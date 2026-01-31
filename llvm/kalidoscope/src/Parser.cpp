#include "Parser.h"
#include "Lexer.h"

static int CurrentToken;
static int GetNextToken() { return CurrentToken = gettok(); }

std::unique_ptr<ExprASTNode> Parser::ParseNumberExpr()
{
    auto Result = std::make_unique<NumberExprASTNode>(NumVal);
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
    std::string IdentName = IdentifierStr;
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
                Args.push_back(Arg);
            } else {
                return nullptr;
            }
            GetNextToken(); // Consume Rparen or Comma
            if (CurrentToken != TOK_COMMA) {
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
    default:
        std::cout << "Error: Token Unexpected.\n";
        exit(1);
    }
}

std::unique_ptr<ExprASTNode> Parser::ParseExpression() {}
