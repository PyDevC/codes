#include "Parser.h"
#include "Errors.h"
#include "Lexer.h"
#include <map>

static int CurrentToken;
static std::unique_ptr<llvm::LLVMContext> Context;
static std::unique_ptr<llvm::IRBuilder<>> Builder;
static std::unique_ptr<llvm::Module> Module;
static std::map<std::string, llvm::Value *> NamedValues;

void GetNextToken() { 
    CurrentToken = gettok(); 
    std::cout << "CurrentToken After calling gettok: " << CurrentToken << std::endl;
}

std::unique_ptr<llvm::Module> getModule() { return std::move(Module); }

llvm::Value *LogErrorV(const char *Str)
{
    LogError(Str);
    return nullptr;
}

static std::map<char, int> BinaryOpPrecedence = {
    {TOK_OPERATOR_ADD, 1},
    {TOK_OPERATOR_SUB, 1},
    {TOK_OPERATOR_MUL, 2},
    {TOK_OPERATOR_DIV, 2},
};

static int GetTokPrecedence()
{
    int Precedence = BinaryOpPrecedence[CurrentToken];
    if (Precedence <= 0)
        return -1;
    return Precedence;
}

llvm::Value *NumberExprASTNode::codegen()
{
    return llvm::ConstantFP::get(*Context, llvm::APFloat(getNumVal()));
}

llvm::Value *VariableExprASTNode::codegen()
{
    llvm::Value *V = NamedValues[m_VarName];
    if (!V) {
        return LogErrorV("Unknown Variable Name");
    }
    return V;
}

llvm::Value *BinaryExprASTNode::codegen()
{
    llvm::Value *Lf = m_Left->codegen();
    llvm::Value *Rg = m_Right->codegen();
    if (!Lf || !Rg) {
        return nullptr;
    }

    switch (m_Op) {
    case '+':
        return Builder->CreateFAdd(Lf, Rg, "addtmp");
    case '-':
        return Builder->CreateFSub(Lf, Rg, "subtmp");
    case '*':
        return Builder->CreateFMul(Lf, Rg, "multmp");
    case '/':
        return Builder->CreateFDiv(Lf, Rg, "multmp");
    default:
        return LogErrorV("Invalid Binary Operator");
    };
}

llvm::Value *CallExprASTNode::codegen()
{
    llvm::Function *CalleeF = Module->getFunction(m_Callee);
    if (!CalleeF) {
        return LogErrorV("Unknown Function call");
    }

    // Argument missmatch error? Can it even happen?
    if (CalleeF->arg_size() != m_Args.size()) {
        return LogErrorV("Incorrect number of arguments are passed");
    }

    std::vector<llvm::Value *> ArgsV;
    for (unsigned i = 0, e = ArgsV.size(); i != e; ++i) {
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
    llvm::Function *Func = Module->getFunction(m_Prototype->getName());

    if (!Func) {
        Func = m_Prototype->codegen();
    }

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
        NamedValues[std::string(Arg.getName())] = &Arg;
    }

    if (llvm::Value *ReturnVal = m_Block->codegen()) {
        Builder->CreateRet(ReturnVal);
        llvm::verifyFunction(*Func);
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
            GetNextToken(); // Consume Lparen or Arg
            if (auto Arg = ParseExpression()) {
                Args.push_back(std::move(Arg));
            } else {
                return nullptr;
            }
            GetNextToken(); // Consume Rparen or Comma
            if (CurrentToken != TOK_COMMA && CurrentToken != TOK_RPAREN) {
                std::cout << "Error: Expected ',' or ')' when passing function "
                             "arguments in surrounded expressions.\n";
                exit(1);
            }
        } while (CurrentToken != TOK_RPAREN);

        auto call =
            std::make_unique<CallExprASTNode>(IdentName, std::move(Args));

        if (CurrentToken != TOK_RPAREN) {
            std::cout
                << "Error: Expected ')' after '(' in surrounded expressions.\n";
            exit(1);
        }
        return call;
    }
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
    case EOF: {
        return nullptr;
    };
    default:
        std::cout << "Error: Token Unexpected received " << CurrentToken << "\n";
        exit(1);
    }
}

static std::unique_ptr<ExprASTNode>
ParseBinaryOpRight(int Precedence, std::unique_ptr<ExprASTNode> Left)
{
    while (1) {
        int CurrentTokenPrecedence = GetTokPrecedence();
        // This means that the priority of lhs is higher than rhs
        if (CurrentTokenPrecedence > Precedence) {
            return Left;
        }
        int BinaryOp = CurrentToken;
        GetNextToken(); // Consume BinaryOp
        Parser parser; 
        // TODO: There is better way to do it I just don't konw yet
        auto Right = parser.ParsePrimaryExpr();
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
    std::cout << "FunctionName: " + FunctionName << "\n";
    GetNextToken(); // Consume Lparen
    if (CurrentToken != TOK_LPAREN) {
        std::cout << CurrentToken << " No ( \n";
        return nullptr;
    }
    std::vector<std::string> Args;
    do {
        // BUG: Fix rn since you are skipping somethings
        GetNextToken(); // Consume Lparen or Arg
        if (CurrentToken == TOK_IDENTIFIER) {
            Args.push_back(getIdentifierStr());
        }
        GetNextToken(); // Consume Rparen or Comma
        if (CurrentToken != TOK_COMMA && CurrentToken != TOK_RPAREN) {
            std::cout << "Error: Expected ',' or ')' when passing function "
                         "arguments in surrounded expressions.\n";
            exit(1);
        }
    } while (CurrentToken != TOK_RPAREN);
    GetNextToken(); // Consume Rparen
    return std::make_unique<PrototypeASTNode>(FunctionName, Args);
}

std::unique_ptr<FunctionASTNode> Parser::ParseFunction()
{
    GetNextToken();

    auto Proto = ParsePrototype();
    if (!Proto) {
        std::cout << "Is NULL:prototype" << "\n";
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
        std::cout << "Parsed" << std::endl;
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

void InitializeModule()
{
    Context = std::make_unique<llvm::LLVMContext>();
    Module = std::make_unique<llvm::Module>("Main INIT", *Context);
    Builder = std::make_unique<llvm::IRBuilder<>>(*Context);
}

void HandleExtern(Parser *parser)
{
    if (auto ProtoAST = parser->ParseExtern()) {
        if (auto *FuncIR = ProtoAST->codegen()) {
            std::cout << "Parsed Extern\n";
            FuncIR->print(llvm::errs());
            fprintf(stderr, "\n");
        }
    } else {
        GetNextToken();
    }
}

void HandleDefinition(Parser *parser)
{
    if (auto FuncAST = parser->ParseFunction()) {
        if (auto *FuncIR = FuncAST->codegen()) {
            std::cout << "Parsed Function def\n";
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
        std::cout << "Parsed";
        if (auto *FuncIR = FuncAST->codegen()) {
            std::cout << "Parsed Toplevel Expression\n";
            FuncIR->print(llvm::errs());
            fprintf(stderr, "\n");
            FuncIR->eraseFromParent();
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
