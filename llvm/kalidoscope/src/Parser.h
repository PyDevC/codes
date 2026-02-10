#pragma once

#include <memory>
#include <string>
#include <vector>

#include <llvm/IR/IRBuilder.h>

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
    std::unique_ptr<ExprASTNode> ParseExpression();
    std::unique_ptr<PrototypeASTNode> ParsePrototype();
    std::unique_ptr<FunctionASTNode> ParseFunction();
    std::unique_ptr<PrototypeASTNode> ParseExtern();
    std::unique_ptr<FunctionASTNode> ParseTopLevelExpr();

    void ParseMain();
};
