#ifndef Lexer_H
#define Lexer_H

typedef enum {
  // Special Characters
  LPAREN,
  RPAREN,
  LBRAC,
  RBRAC,
  LBRACE,
  RBRACE,
  SEMICOLON,
  EQUAL,
  NOTEQUAL,
  // General characters and others
  OPERATOR,
  KEYWORD,
  VARIABLE,
  DTYPE,
  LITERAL,
  LITERALSTRING,
  // Adding Illegal for everyother character that doesn't match anything above
  ILLEGAL
} Token;

typedef struct SToken {
  char *literal;
  Token Tokentype;
} SToken;

typedef enum { ADD, MUL, SUB, DIV, FLOOR } Operator;
typedef enum { _INT, _CHAR, _FLOOR, _DOUBLE, _LONG, _STRING } dtypes;

// Function declarations
SToken *Tokenizer(char **stream); // Stream of characters

#endif // Lexer_H
