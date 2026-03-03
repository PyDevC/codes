#include "Parser.h"
#include "Errors.h"
#include "Target.h"
#include "Lexer.h"
#include <map>

static int CurrentToken;
static std::unique_ptr<llvm::LLVMContext> Context;
static std::unique_ptr<llvm::IRBuilder<>> Builder;
static std::unique_ptr<llvm::Module> Module;
static std::map<std::string, llvm::AllocaInst *> NamedValues;

std::unique_ptr<llvm::orc::KaleidoscopeJIT> TheJIT;
static std::unique_ptr<llvm::FunctionPassManager> FuncPass_M;
static std::unique_ptr<llvm::LoopAnalysisManager> LoopAnaysis_M;
static std::unique_ptr<llvm::FunctionAnalysisManager> FuncAnalysis_M;
static std::unique_ptr<llvm::CGSCCAnalysisManager> CGSCCAnalysis_M;
static std::unique_ptr<llvm::ModuleAnalysisManager> ModuleAnalysis_M;
static std::unique_ptr<llvm::PassInstrumentationCallbacks> PassInstCallbacks;
static std::unique_ptr<llvm::StandardInstrumentations> StdInst;
static std::map<std::string, std::unique_ptr<PrototypeASTNode>> FunctionProtos;
static llvm::ExitOnError ExitOnErr;

static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *func,
                                                llvm::StringRef VarName)
{
    llvm::IRBuilder<> TmpB(&func->getEntryBlock(),
                           func->getEntryBlock().begin());
    return TmpB.CreateAlloca(llvm::Type::getDoubleTy(*Context), nullptr,
                             VarName);
}

void GetNextToken() { CurrentToken = gettok(); }

std::unique_ptr<llvm::Module> getModule() { return std::move(Module); }
llvm::ExitOnError getExitOnError() { return ExitOnErr; }

llvm::Value *LogErrorV(const char *Str)
{
    LogError(Str);
    return nullptr;
}

static std::map<char, int> BinaryOpPrecedence = {
    {TOK_OPERATOR_ADD, 10}, {TOK_OPERATOR_SUB, 10}, {TOK_OPERATOR_MUL, 20},
    {TOK_OPERATOR_DIV, 20}, {TOK_OPERATOR_LT, 30},  {TOK_OPERATOR_GT, 30},
    {TOK_OPERATOR_LTE, 30}, {TOK_OPERATOR_GTE, 30},
};

static int GetTokPrecedence()
{
    int Precedence = BinaryOpPrecedence[CurrentToken];
    if (Precedence <= 0) {
        return -1;
    }
    return Precedence;
}

llvm::Function *getFunction(std::string Name)
{
    if (auto *F = Module->getFunction(Name)) {
        return F;
    }

    auto FExists = FunctionProtos.find(Name);
    if (FExists != FunctionProtos.end()) {
        return FExists->second->codegen();
    }
    return nullptr;
}

llvm::Value *NumberExprASTNode::codegen()
{
    return llvm::ConstantFP::get(*Context, llvm::APFloat(m_NumberVal));
}

llvm::Value *VariableExprASTNode::codegen()
{
    llvm::AllocaInst *V = NamedValues[m_VarName];
    if (!V) {
        return LogErrorV("Unknown Variable Name");
    }
    return Builder->CreateLoad(V->getAllocatedType(), V, m_VarName.c_str());
}

llvm::Value *VarASTNode::codegen()
{
    std::vector<llvm::AllocaInst *> OldBindings;
    llvm::Function *Func = Builder->GetInsertBlock()->getParent();

    for (unsigned i = 0, e = m_VarNames.size(); i != e; ++i) {
        const std::string &VarName = m_VarNames[i].first;
        ExprASTNode *Init = m_VarNames[i].second.get();
        llvm::Value *InitVal;
        if (Init) {
            InitVal = Init->codegen();
            if (!InitVal) {
                return nullptr;
            }
        } else {
            InitVal = llvm::ConstantFP::get(*Context, llvm::APFloat(0.0));
        }
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Func, VarName);
        Builder->CreateStore(InitVal, Alloca);
        OldBindings.push_back(NamedValues[VarName]);
        NamedValues[VarName] = Alloca;
    }

    llvm::Value *Body = m_Body->codegen();
    if (!Body) {
        return nullptr;
    }

    for (unsigned i = 0, e = m_VarNames.size(); i != e; ++i) {
        NamedValues[m_VarNames[i].first] = OldBindings[i];
    }

    return Body;
}

llvm::Value *IfExprASTNode::codegen()
{
    llvm::Value *Cond = m_Condition->codegen();
    if (!Cond) {
        return nullptr;
    }

    Cond = Builder->CreateFCmpONE(
        Cond, llvm::ConstantFP::get(*Context, llvm::APFloat(0.0)),
        "ifcondition");
    llvm::Function *func = Builder->GetInsertBlock()->getParent();

    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(*Context, "then", func);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(*Context, "else");
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(*Context, "ifcont");

    Builder->CreateCondBr(Cond, ThenBB, ElseBB);
    Builder->SetInsertPoint(ThenBB);

    llvm::Value *Then = m_ThenExpr->codegen();
    if (!Then) {
        return nullptr;
    }

    Builder->CreateBr(MergeBB);
    ThenBB = Builder->GetInsertBlock();

    func->insert(func->end(), ElseBB);
    Builder->SetInsertPoint(ElseBB);

    llvm::Value *Else = m_ElseExpr->codegen();
    if (!Else) {
        return nullptr;
    }

    Builder->CreateBr(MergeBB);
    ElseBB = Builder->GetInsertBlock();

    func->insert(func->end(), MergeBB);
    Builder->SetInsertPoint(MergeBB);
    llvm::PHINode *phi =
        Builder->CreatePHI(llvm::Type::getDoubleTy(*Context), 2, "iftmp");
    phi->addIncoming(Then, ThenBB);
    phi->addIncoming(Else, ElseBB);

    return phi;
}

llvm::Value *ForExprASTNode::codegen()
{
    llvm::Function *func = Builder->GetInsertBlock()->getParent();
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(func, m_VarName);

    llvm::Value *Init = m_Init->codegen();
    if (!Init) {
        return nullptr;
    }

    Builder->CreateStore(Init, Alloca);

    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(*Context, "loop", func);

    Builder->CreateBr(LoopBB);
    Builder->SetInsertPoint(LoopBB);

    llvm::AllocaInst *OldVal = NamedValues[m_VarName];
    NamedValues[m_VarName] = Alloca;

    llvm::Value *Body = m_Body->codegen();
    if (!Body) {
        return nullptr;
    }

    llvm::Value *Step = nullptr;
    if (m_Step) {
        Step = m_Step->codegen();
        if (!Step) {
            return nullptr;
        }
    } else {
        Step = llvm::ConstantFP::get(*Context, llvm::APFloat(1.0));
    }

    llvm::Value *EndCond = m_Condition->codegen();
    if (!EndCond) {
        return nullptr;
    }

    llvm::Value *CurrVar = Builder->CreateLoad(Alloca->getAllocatedType(),
                                               Alloca, m_VarName.c_str());
    llvm::Value *NextVar = Builder->CreateFAdd(CurrVar, Step, "nextval");
    Builder->CreateStore(NextVar, Alloca);

    EndCond = Builder->CreateFCmpONE(
        EndCond, llvm::ConstantFP::get(*Context, llvm::APFloat(0.0)),
        "loopcond");

    llvm::BasicBlock *AfterBB =
        llvm::BasicBlock::Create(*Context, "afterloop", func);

    Builder->CreateCondBr(EndCond, LoopBB, AfterBB);
    Builder->SetInsertPoint(AfterBB);

    if (OldVal) {
        NamedValues[m_VarName] = OldVal;
    } else {
        NamedValues.erase(m_VarName);
    }

    return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(*Context));
}

llvm::Value *BinaryExprASTNode::codegen()
{
    // Special Assignment case
    if (m_Op == '=') {
        VariableExprASTNode *Lf =
            static_cast<VariableExprASTNode *>(m_Left.get());
        if (!Lf) {
            return LogErrorV(
                "Syntax Error: Assignment should be applied to a variable.");
        }
        llvm::Value *Rg = m_Right->codegen();
        if (!Rg) {
            return nullptr;
        }
        llvm::Value *variable = NamedValues[Lf->getName()];
        if (!variable) {
            return LogErrorV("Unknown Variable name.");
        }
        Builder->CreateStore(Rg, variable);
        return Rg;
    }

    llvm::Value *Lf = m_Left->codegen();
    llvm::Value *Rg = m_Right->codegen();
    if (!Lf || !Rg) {
        return nullptr;
    }

    switch (m_Op) {
    case TOK_OPERATOR_ADD:
        return Builder->CreateFAdd(Lf, Rg, "addtmp");
    case TOK_OPERATOR_SUB:
        return Builder->CreateFSub(Lf, Rg, "subtmp");
    case TOK_OPERATOR_MUL:
        return Builder->CreateFMul(Lf, Rg, "multmp");
    case TOK_OPERATOR_DIV:
        return Builder->CreateFDiv(Lf, Rg, "divtmp");
    case TOK_OPERATOR_LT:
        Lf = Builder->CreateFCmpULT(Lf, Rg, "lttmp");
        return Builder->CreateUIToFP(Lf, llvm::Type::getDoubleTy(*Context),
                                     "booltmp");
    case TOK_OPERATOR_LTE:
        Lf = Builder->CreateFCmpULE(Lf, Rg, "ltetmp");
        return Builder->CreateUIToFP(Lf, llvm::Type::getDoubleTy(*Context),
                                     "booltmp");
    case TOK_OPERATOR_GT:
        Lf = Builder->CreateFCmpUGT(Lf, Rg, "gttmp");
        return Builder->CreateUIToFP(Lf, llvm::Type::getDoubleTy(*Context),
                                     "booltmp");
    case TOK_OPERATOR_GTE:
        Lf = Builder->CreateFCmpUGE(Lf, Rg, "gtetmp");
        return Builder->CreateUIToFP(Lf, llvm::Type::getDoubleTy(*Context),
                                     "booltmp");
    default:
        break;
    };

    // Checking for function call
    llvm::Function *func = getFunction(std::string("binary") + m_Op);
    assert(func && "binary operator not found!");

    llvm::Value *Ops[] = {Lf, Rg};
    return Builder->CreateCall(func, Ops, "binaryop");
}

llvm::Value *CallExprASTNode::codegen()
{
    llvm::Function *CalleeF = getFunction(m_Callee);
    if (!CalleeF) {
        return LogErrorV("Unknown Function call");
    }

    // Argument missmatch error? Can it even happen?
    if (CalleeF->arg_size() != m_Args.size()) {
        return LogErrorV("Incorrect number of arguments are passed");
    }

    std::vector<llvm::Value *> ArgsV;
    for (unsigned i = 0, e = m_Args.size(); i != e; ++i) {
        ArgsV.push_back(m_Args[i]->codegen());
        if (!ArgsV.back()) {
            return nullptr;
        }
    }
    return Builder->CreateCall(CalleeF, ArgsV, "calltmp");
}

llvm::Function *PrototypeASTNode::codegen()
{
    std::vector<llvm::Type *> Doubles(m_Args.size(),
                                      llvm::Type::getDoubleTy(*Context));

    llvm::FunctionType *FuncType = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(*Context), Doubles, false);

    llvm::Function *Func =
        llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage,
                               m_PrototypeName, Module.get());

    unsigned Idx = 0;
    for (auto &Arg : Func->args()) {
        Arg.setName(m_Args[Idx++]);
    }
    return Func;
}

llvm::Function *FunctionASTNode::codegen()
{
    auto &P = *m_Prototype;
    FunctionProtos[m_Prototype->getName()] = std::move(m_Prototype);
    llvm::Function *Func = getFunction(P.getName());

    if (!Func) {
        return nullptr;
    }

    if (!Func->empty()) {
        return (llvm::Function *)LogErrorV("Function cannot be redefined");
    }

    llvm::BasicBlock *BBlock =
        llvm::BasicBlock::Create(*Context, "entry", Func);
    Builder->SetInsertPoint(BBlock);

    NamedValues.clear();
    for (auto &Arg : Func->args()) {
        llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Func, Arg.getName());
        Builder->CreateStore(&Arg, Alloca);
        NamedValues[std::string(Arg.getName())] = Alloca;
    }

    if (llvm::Value *ReturnVal = m_Block->codegen()) {
        Builder->CreateRet(ReturnVal);
        llvm::verifyFunction(*Func);
        FuncPass_M->run(*Func, *FuncAnalysis_M);
        return Func;
    }
    Func->eraseFromParent();
    return nullptr;
}

std::unique_ptr<ExprASTNode> Parser::ParseNumberExpr()
{
    auto Result = std::make_unique<NumberExprASTNode>(getNumVal());
    GetNextToken(); // Consume Number
    return std::move(Result);
}

std::unique_ptr<ExprASTNode> Parser::ParseParenExpr()
{
    GetNextToken(); // Consume Lparen
    auto Expr = ParseExpression();
    if (!Expr) {
        return nullptr;
    }
    if (CurrentToken != TOK_RPAREN) {
        std::cout
            << "Error: Expected ')' after '(' in surrounded expressions.\n";
        exit(1);
    }
    GetNextToken(); // Consume Rparen
    return std::move(Expr);
}

std::unique_ptr<ExprASTNode> Parser::ParseIdentifierExpr()
{
    std::string IdentName = getIdentifierStr();
    GetNextToken(); // Consume Identifier
    // Check for function call
    if (CurrentToken != TOK_LPAREN) {
        return std::make_unique<VariableExprASTNode>(IdentName);
    } else {
        // parse args
        std::vector<std::unique_ptr<ExprASTNode>> Args;
        do {
            GetNextToken(); // Consume Lparen
            if (auto Arg = ParseExpression()) {
                Args.push_back(std::move(Arg));
            } else {
                GetNextToken(); // Consume Rparen
                return nullptr;
            }
            if (CurrentToken != TOK_COMMA && CurrentToken != TOK_RPAREN) {
                std::cout << "Error: Expected ',' or ')' when passing function "
                             "arguments in surrounded expressions.\n";
                exit(1);
            }
        } while (CurrentToken != TOK_RPAREN); // Break the loop

        auto call =
            std::make_unique<CallExprASTNode>(IdentName, std::move(Args));

        if (CurrentToken != TOK_RPAREN) {
            std::cout
                << "Error: Expected ')' after '(' in surrounded expressions.\n";
            exit(1);
        }
        GetNextToken();
        return call;
    }
}

std::unique_ptr<ExprASTNode> Parser::ParseVarExpr()
{
    GetNextToken(); // Consume LOCAL keyword

    std::vector<std::pair<std::string, std::unique_ptr<ExprASTNode>>> VarNames;
    if (CurrentToken != TOK_IDENTIFIER) {
        LogError("Syntax Error: Expected identifier after keyword var.");
    }

    while (true) {
        std::string Name = getIdentifierStr();
        GetNextToken(); // Consume Identifier

        std::unique_ptr<ExprASTNode> Init;
        if (CurrentToken == TOK_EQUAL) {
            GetNextToken();
            Init = ParseExpression();
            if (!Init) {
                return nullptr;
            }
        }

        VarNames.push_back(std::make_pair(Name, std::move(Init)));
        if (CurrentToken != TOK_COMMA) {
            break;
        }
        GetNextToken(); // Consume COMMA
        if (CurrentToken != TOK_IDENTIFIER) {
            LogError("Syntax Error: Expected Identifier List after var");
        }
    }

    if (CurrentToken == TOK_KEYWORD) {
        Keywords keywords;
        Keyword keytoken = keywords.KeywordToCode(getIdentifierStr().c_str(),
                                                  getIdentifierStr().size());
        if (keytoken != KEYWORD_IN) {
            LogError("Syntax Error: Expected keyword in after var list.");
        }
        GetNextToken(); // Consume IN Keyword
        auto Body = ParseExpression();
        if (!Body) {
            return nullptr;
        }
        return std::make_unique<VarASTNode>(std::move(VarNames),
                                            std::move(Body));
    } else {
        LogError("Syntax Error: Expected keyword in after var list.");
        return nullptr;
    }
}

std::unique_ptr<ExprASTNode> Parser::ParseIfExpr()
{
    GetNextToken(); // Consume IF keyword

    auto Cond = ParseExpression();
    if (!Cond) {
        std::cout << "Syntax Error: if expressions require a condition.\n";
        exit(1);
    }

    if (CurrentToken == TOK_KEYWORD) {
        Keywords keywords;
        Keyword keytoken = keywords.KeywordToCode(getIdentifierStr().c_str(),
                                                  getIdentifierStr().size());
        if (keytoken != KEYWORD_THEN) {
            LogError("Syntax Error: missing then keyword after if expression "
                     "condition.\n");
        }
    }

    GetNextToken(); // Consume then keyword
    auto ThenExpr = ParseExpression();
    if (!ThenExpr) {
        std::cout << "Syntax Error: expected expression after then keyword.\n";
        exit(1);
    }

    if (CurrentToken == TOK_KEYWORD) {
        Keywords keywords;
        Keyword keytoken = keywords.KeywordToCode(getIdentifierStr().c_str(),
                                                  getIdentifierStr().size());
        if (keytoken != KEYWORD_ELSE) {
            LogError("Syntax Error: missing else keyword after then expression "
                     "condition.\n");
        }
    } else {
        return std::make_unique<IfExprASTNode>(std::move(Cond),
                                               std::move(ThenExpr), nullptr);
    }

    GetNextToken(); // Consume else keyword
    auto ElseExpr = ParseExpression();
    if (!ElseExpr) {
        std::cout << "Syntax Error: expected expression after else keyword.\n";
        exit(1);
    }

    return std::make_unique<IfExprASTNode>(std::move(Cond), std::move(ThenExpr),
                                           std::move(ElseExpr));
}

std::unique_ptr<ExprASTNode> Parser::ParseForExpr()
{
    GetNextToken(); // Consume for keyword

    if (CurrentToken != TOK_IDENTIFIER) {
        LogError("Syntax Error: Init should be an Identifier.");
    }

    std::string IdentName = getIdentifierStr();
    GetNextToken(); // Consume Identifier

    if (CurrentToken != TOK_EQUAL) {
        LogError("Syntax Error: no assignment to the Identifier.");
    }

    GetNextToken(); // Consume EQUAL

    auto Init = ParseExpression();
    if (!Init) {
        LogError("Syntax Error: No expression after for keyword.");
    }

    if (CurrentToken != TOK_COMMA) {
        LogError(
            "Syntax Error: comma missing after init condition in for loop.");
    }

    GetNextToken(); // Consume COMMA

    auto Cond = ParseExpression();
    if (!Cond) {
        LogError("Syntax Error: No expression after init for 'for' loop.");
    }

    if (CurrentToken != TOK_COMMA) {
        LogError("Syntax Error: comma missing after terminating condition in "
                 "for loop.");
    }

    GetNextToken(); // Consume COMMA

    auto Step = ParsePrimaryExpr();
    if (!Step) {
        LogError(
            "Syntax Error: No step after terminating condition in 'for' loop.");
    }

    if (CurrentToken == TOK_KEYWORD) {
        Keywords keywords;
        Keyword keytoken = keywords.KeywordToCode(getIdentifierStr().c_str(),
                                                  getIdentifierStr().size());
        if (keytoken != KEYWORD_IN) {
            LogError("Syntax Error: Expected in keyword after step expression "
                     "of for loop.");
        }
    }

    GetNextToken(); // Consume IN

    auto Body = ParseExpression();
    if (!Body) {
        LogError("Syntax Error: No body for the for loop");
    }

    return std::make_unique<ForExprASTNode>(IdentName, std::move(Init),
                                            std::move(Cond), std::move(Step),
                                            std::move(Body));
}

std::unique_ptr<ExprASTNode> Parser::ParsePrimaryExpr()
{
    switch (CurrentToken) {
    case TOK_IDENTIFIER: {
        return ParseIdentifierExpr();
    } break;
    case TOK_NUMVAL: {
        return ParseNumberExpr();
    } break;
    case TOK_LPAREN: {
        return ParseParenExpr();
    } break;
    case TOK_KEYWORD: {
        Keywords keywords;
        // We are practically repeating exactly same code here and can change it
        // but not righting performance code so leave it.
        Keyword keytoken = keywords.KeywordToCode(getIdentifierStr().c_str(),
                                                  getIdentifierStr().size());
        switch (keytoken) {
        case KEYWORD_IF:
            return ParseIfExpr();
        case KEYWORD_FOR:
            return ParseForExpr();
        case KEYWORD_LOCAL:
            return ParseVarExpr();
        default:
            std::cout << "Error: Keyword Not implemented.\n";
            exit(1);
        };
    } break;
    case EOF: {
        return nullptr;
    };
    default:
        std::cout << "Error: Token Unexpected received " << CurrentToken
                  << "\n";
        exit(1);
    }
}

std::unique_ptr<ExprASTNode>
Parser::ParseBinaryOpRight(int Precedence, std::unique_ptr<ExprASTNode> Left)
{
    while (1) {
        int CurrentTokenPrecedence = GetTokPrecedence();
        // This means that the priority of lhs is higher than rhs
        if (CurrentTokenPrecedence < Precedence) {
            return Left;
        }
        int BinaryOp = CurrentToken;
        GetNextToken(); // Consume BinaryOp

        // TODO: There is better way to do it I just don't konw yet
        auto Right = ParsePrimaryExpr();
        if (!Right) {
            return nullptr;
        }
        int NextPrecedence = GetTokPrecedence();
        if (CurrentTokenPrecedence < NextPrecedence) {
            Right = ParseBinaryOpRight(CurrentTokenPrecedence + 1,
                                       std::move(Right));
            if (!Right) {
                return nullptr;
            }
        }
        Left = std::make_unique<BinaryExprASTNode>(BinaryOp, std::move(Left),
                                                   std::move(Right));
    }
}

std::unique_ptr<ExprASTNode> Parser::ParseExpression()
{
    auto Left = ParsePrimaryExpr();
    if (!Left) {
        return nullptr;
    }
    return ParseBinaryOpRight(0, std::move(Left));
}

std::unique_ptr<PrototypeASTNode> Parser::ParsePrototype()
{
    if (CurrentToken != TOK_IDENTIFIER) {
        return nullptr;
    }
    std::string FunctionName = getIdentifierStr();
    GetNextToken(); // Consume Identifier
    if (CurrentToken != TOK_LPAREN) {
        LogError("Expected a ( but got none");
        return nullptr;
    }
    GetNextToken(); // Consume Lparen
    std::vector<std::string> Args;

    if(CurrentToken != TOK_RPAREN) {
        while(true){
            if(CurrentToken == TOK_IDENTIFIER){
                Args.push_back(getIdentifierStr());
                GetNextToken(); // Consume Identifier
            }
            if(CurrentToken == TOK_RPAREN){
                break;
            }
            if(CurrentToken != TOK_COMMA) {
                LogError("Syntax Error: Expected ',' or ')'.");
                exit(1);
            }
            GetNextToken(); // Consume COMMA
        }
    }
    GetNextToken(); // Consume Rparen
    return std::make_unique<PrototypeASTNode>(FunctionName, Args);
}

std::unique_ptr<FunctionASTNode> Parser::ParseFunction()
{
    GetNextToken();

    auto Proto = ParsePrototype();
    if (!Proto) {
        return nullptr;
    }

    if (auto E = ParseExpression()) {
        return std::make_unique<FunctionASTNode>(std::move(Proto),
                                                 std::move(E));
    }
    return nullptr;
}

std::unique_ptr<PrototypeASTNode> Parser::ParseExtern()
{
    GetNextToken();
    return ParsePrototype();
}

std::unique_ptr<FunctionASTNode> Parser::ParseTopLevelExpr()
{
    if (auto E = ParseExpression()) {
        auto Proto = std::make_unique<PrototypeASTNode>(
            "__anon_expr", std::vector<std::string>());
        // Passing empty list of arguments for prototype
        return std::make_unique<FunctionASTNode>(std::move(Proto),
                                                 std::move(E));
    }
    return nullptr;
}

//===----------------------------------------------------------------------===//
// Main Parser Helper Handles
//===----------------------------------------------------------------------===//

void InitializeModuleAndManagers()
{
    Context = std::make_unique<llvm::LLVMContext>();
    Module = std::make_unique<llvm::Module>("Main INIT", *Context);
    Builder = std::make_unique<llvm::IRBuilder<>>(*Context);
    Module->setDataLayout(TheJIT->getDataLayout());

    // Pass Managers
    FuncPass_M = std::make_unique<llvm::FunctionPassManager>();
    LoopAnaysis_M = std::make_unique<llvm::LoopAnalysisManager>();
    FuncAnalysis_M = std::make_unique<llvm::FunctionAnalysisManager>();
    CGSCCAnalysis_M = std::make_unique<llvm::CGSCCAnalysisManager>();
    ModuleAnalysis_M = std::make_unique<llvm::ModuleAnalysisManager>();
    PassInstCallbacks = std::make_unique<llvm::PassInstrumentationCallbacks>();
    StdInst = std::make_unique<llvm::StandardInstrumentations>(*Context, true);

    StdInst->registerCallbacks(*PassInstCallbacks, ModuleAnalysis_M.get());

    // Adding Transform Passes
    FuncPass_M->addPass(llvm::PromotePass());
    FuncPass_M->addPass(llvm::InstCombinePass());
    FuncPass_M->addPass(llvm::ReassociatePass());
    FuncPass_M->addPass(llvm::GVNPass());
    FuncPass_M->addPass(llvm::SimplifyCFGPass());

    // Register Analysis Passes
    llvm::PassBuilder PBuilder;
    PBuilder.registerModuleAnalyses(*ModuleAnalysis_M);
    PBuilder.registerFunctionAnalyses(*FuncAnalysis_M);
    PBuilder.crossRegisterProxies(*LoopAnaysis_M, *FuncAnalysis_M,
                                  *CGSCCAnalysis_M, *ModuleAnalysis_M, nullptr);
}

void HandleExtern(Parser *parser)
{
    if (auto ProtoAST = parser->ParseExtern()) {
        if (auto *FuncIR = ProtoAST->codegen()) {
            FuncIR->print(llvm::errs());
            fprintf(stderr, "\n");
            FunctionProtos[ProtoAST->getName()] = std::move(ProtoAST);
        }
    } else {
        GetNextToken();
    }
}

void HandleDefinition(Parser *parser)
{
    if (auto FuncAST = parser->ParseFunction()) {
        if (auto *FuncIR = FuncAST->codegen()) {
            fprintf(stderr, "Read function definition:\n");
            FuncIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        GetNextToken();
    }
}

void HandelTopLevelExpr(Parser *parser)
{
    if (auto FuncAST = parser->ParseTopLevelExpr()) {
        if (auto *FuncIR = FuncAST->codegen()) {
            fprintf(stderr, "Read top level expression:\n");
            FuncIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        GetNextToken();
    }
}

void Parser::ParseMain()
{
    GetNextToken();
    switch (CurrentToken) {
    case TOK_EOF:
        return;
    case TOK_KEYWORD: {
        Keywords keywords;
        // We are practically repeating exactly same code here and can change it
        // but not righting performance code so leave it.
        Keyword keytoken = keywords.KeywordToCode(getIdentifierStr().c_str(),
                                                  getIdentifierStr().size());
        switch (keytoken) {
        case KEYWORD_FUNCTION:
            HandleDefinition(this);
            break;
        case KEYWORD_EXTERN:
            HandleExtern(this);
            break;
        default:
            return;
        };
    } break;
    default:
        HandelTopLevelExpr(this);
        break;
    };
}

extern "C" DLLEXPORT double putchard(double X)
{
    fputc((char)X, stderr);
    return 1.0;
}

extern "C" DLLEXPORT double printd(double X)
{
    fprintf(stderr, "%f\n", X);
    return 1.0;
}
