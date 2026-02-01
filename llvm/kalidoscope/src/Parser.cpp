#include "Parser.h"
#include "Lexer.h"
#include <map>

static int CurrentToken;
static void GetNextToken() { CurrentToken = gettok(); }

static std::map<char, int> BinaryOpPrecedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
};

static int GetTokPrecedence()
{
    if (!isascii(CurrentToken)) {
        return -1;
    }

    int Precedence = BinaryOpPrecedence[CurrentToken];
    if (Precedence <= 0)
        return -1;
    return Precedence;
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
        std::cout << "Error: Token Unexpected.\n";
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
        Parser
            parser; // TODO: There is better way to do it I just don't konw yet
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
    GetNextToken();
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
    GetNextToken(); // Consume Lparen
    if (CurrentToken != TOK_LPAREN) {
        return nullptr;
    }
    std::vector<std::string> Args;
    do {
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
    return std::make_unique<PrototypeASTNode>(FunctionName, Args);
}
