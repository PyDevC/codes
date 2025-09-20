#ifndef LEXER_H
#define LEXER_H

typedef enum {
  TypeIllegal,
  TypeArithimeticOperator,
  TypeKeyword,
  TypeSemiColon,
  TypeIdentifier,
  TypeEqual,
  TypeLiteral
} TokenType;

typedef struct Token {
  TokenType type;
  char *placeholder;
} Token;

Token *tokenizer(char **stream, Token *tokens);
Token tokenIdentifier(char *token);

#endif
