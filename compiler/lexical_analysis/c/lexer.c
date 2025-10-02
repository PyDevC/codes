#include "lexer.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allocates the new size to the "type"
void DynamicSizeAllocator(size_t *type) {
  size_t currsize = sizeof(type);
  size_t newsize = currsize * 2;
  type = realloc(type, currsize);
}

SToken ReadTokenType(char *tokenchars) {
  // Check for special characters
  SToken stoken;
  stoken.literal = tokenchars;
  stoken.Tokentype = ILLEGAL;
  if (strlen(tokenchars) == 1) {
    char tokenchar = tokenchars[0];
    switch (tokenchar) {
    // Special Characters
    case '{':
      stoken.Tokentype = LBRACE;
      break;
    case '}':
      stoken.Tokentype = RBRACE;
      break;
    case '(':
      stoken.Tokentype = LPAREN;
      break;
    case ')':
      stoken.Tokentype = RPAREN;
      break;
    case '[':
      stoken.Tokentype = LBRAC;
      break;
    case ']':
      stoken.Tokentype = RBRAC;
      break;
    case ';':
      stoken.Tokentype = SEMICOLON;
      break;
    case '=':
      stoken.Tokentype = EQUAL;
      break;
    // Operators
    case '+':
    case '-':
    case '/':
    case '*':
      stoken.Tokentype = OPERATOR;
      break;
    };
  } else {

    // REGEX match for literal
    regex_t regex;
    int reti;
    reti = regcomp(&regex, "^[0-9]+$", 0);
    reti = regexec(&regex, tokenchars, 0, NULL, 0);
    if (reti) {
      stoken.Tokentype = LITERAL;
    }

    // Match for Keywords
    char *keyword_array[] = {"function", "end", "return", "local", "do",
                             "while",    "for", "if",     "then"};
    char *keyword;
    int idx;

    for (idx = 0; idx < 8; idx++) {
      keyword = keyword_array[idx];
      if (strcmp(tokenchars, keyword) == 0) {
        stoken.Tokentype = KEYWORD;
        break;
      }
    }

    // REGEX match for String literal
    reti = regcomp(&regex, "^[0-9,a-z,A-Z]+$", 0);
    reti = regexec(&regex, tokenchars, 0, NULL, 0);
    if (reti) {
      stoken.Tokentype = LITERAL;
    }
    // Match rules for variable name
  }
  return stoken;
}

SToken *Tokenizer(char **stream) {
  SToken *TokenList = malloc((**stream) * sizeof(SToken));
  int i;
  for (i = 0; i < 4; i++) {
    TokenList[i] = ReadTokenType(stream[i]);
  }
  return TokenList;
}
