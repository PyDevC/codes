#pragma once

#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/IRBuilder.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/StandardInstrumentations.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Scalar/Reassociate.h"
#include "llvm/Transforms/Scalar/SimplifyCFG.h"

#include "../include/KaleidoscopeJIT.h"

void GetNextToken();

llvm::Value *LogErrorV(const char* Str);

// Base Class for all Nodes
// List of Different types of Nodes:
// - ExprASTNode
// - BlockASTNode
// - IfASTNode
// - WhileASTNode
class ASTNode
{
  public:
    virtual ~ASTNode() = default;
};

class ExprASTNode : public ASTNode
{
  private:
    int m_ExprType;

  public:
    ExprASTNode() {}
    virtual ~ExprASTNode() override {}
    virtual llvm::Value* codegen() = 0;
};

class NumberExprASTNode : public ExprASTNode
{
  private:
    double m_NumberVal;

  public:
    NumberExprASTNode(double NumberVal) : m_NumberVal(NumberVal) {}
    ~NumberExprASTNode() override {}
    llvm::Value *codegen() override;
};

class VariableExprASTNode : public ExprASTNode
{
  private:
    std::string m_VarName;
    std::string m_VarType;

  public:
    VariableExprASTNode(const std::string &VarName) : m_VarName(VarName) {}
    ~VariableExprASTNode() override {}
    llvm::Value *codegen() override;
};

class BinaryExprASTNode : public ExprASTNode
{
  private:
    char m_Op;
    std::unique_ptr<ExprASTNode> m_Left, m_Right;

  public:
    BinaryExprASTNode(char Op, std::unique_ptr<ExprASTNode> Left,
                      std::unique_ptr<ExprASTNode> Right)
        : m_Op(Op), m_Left(std::move(Left)), m_Right(std::move(Right))
    {
    }
    ~BinaryExprASTNode() override {}
    llvm::Value *codegen() override;
};

class UnaryExprASTNode : public ExprASTNode
{
  private:
    char m_Op;
    std::unique_ptr<ExprASTNode> m_Right;

  public:
    UnaryExprASTNode(char Op, std::unique_ptr<ExprASTNode> Right)
        : m_Op(Op), m_Right(std::move(Right))
    {
    }
    ~UnaryExprASTNode() override {}
};

class CallExprASTNode : public ExprASTNode
{
  private:
    std::string m_Callee;
    std::vector<std::unique_ptr<ExprASTNode>> m_Args;

  public:
    CallExprASTNode(const std::string Callee,
                    std::vector<std::unique_ptr<ExprASTNode>> Args)
        : m_Callee(Callee), m_Args(std::move(Args))
    {
    }
    ~CallExprASTNode() override {}
    llvm::Value* codegen() override;
};

class BlockASTNode : public ASTNode
{
  private:
    std::vector<ASTNode> m_StatementASTNode;
};

class PrototypeASTNode : public ASTNode
{
  private:
    std::string m_PrototypeName;
    std::vector<std::string> m_Args;

  public:
    PrototypeASTNode(const std::string &Name, std::vector<std::string> Args)
        : m_PrototypeName(Name), m_Args(Args)
    {
    }

    std::string getName() const {return m_PrototypeName;}
    ~PrototypeASTNode() override {}
    llvm::Function* codegen();
};

class FunctionASTNode : public ASTNode
{
  private:
    std::unique_ptr<PrototypeASTNode> m_Prototype;
    std::unique_ptr<ExprASTNode> m_Block;

  public:
    FunctionASTNode(std::unique_ptr<PrototypeASTNode> Prototype,
                    std::unique_ptr<ExprASTNode> Block)
        : m_Prototype(std::move(Prototype)), m_Block(std::move(Block))
    {
    }
    ~FunctionASTNode() override {}
    llvm::Function* codegen();
};

class Parser
{
  private:
    std::unique_ptr<ASTNode> m_Root;

  public:
    std::unique_ptr<ExprASTNode> ParseNumberExpr();
    std::unique_ptr<ExprASTNode> ParseParenExpr();
    std::unique_ptr<ExprASTNode> ParseIdentifierExpr();
    std::unique_ptr<ExprASTNode> ParsePrimaryExpr();
    std::unique_ptr<ExprASTNode> ParseBinaryOpRight(int, std::unique_ptr<ExprASTNode>);
    std::unique_ptr<ExprASTNode> ParseExpression();
    std::unique_ptr<PrototypeASTNode> ParsePrototype();
    std::unique_ptr<FunctionASTNode> ParseFunction();
    std::unique_ptr<PrototypeASTNode> ParseExtern();
    std::unique_ptr<FunctionASTNode> ParseTopLevelExpr();

    void ParseMain();
};

void InitializeModuleAndManagers();
std::unique_ptr<llvm::Module> getModule();
extern std::unique_ptr<llvm::orc::KaleidoscopeJIT> TheJIT;
llvm::ExitOnError getExitOnError();

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT double putchard(double X);
extern "C" DLLEXPORT double printd(double X);
