#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkString(const char *s) {
  unsigned char c = s[0];
  int j = 1;
  int i = 0;
  int size = strlen(s);
  while (c != '\0') {
    if (isalpha(c))
      i++;
    c = s[j];
    j++;
  }
  return size == i;
}

int checkNumber(const char *s) {
  unsigned char c = s[0];
  int j = 1;
  int i = 0;
  int size = strlen(s);
  while (c != '\0') {
    if (isdigit(c))
      i++;
    c = s[j];
    j++;
  }
  return size == i;
}

Token tokenIdentifier(char *token) {
  Token stoken;
  stoken.placeholder = token;
  if (strcmp(token, "=") == 0) {
    stoken.type = TypeEqual;

  } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
             strcmp(token, "/") == 0 || strcmp(token, "*") == 0) {

    stoken.type = TypeArithimeticOperator;

  } else if (strcmp(token, "local") == 0 || strcmp(token, "function") == 0 ||
             strcmp(token, "return") == 0 || strcmp(token, "end") == 0) {

    stoken.type = TypeKeyword;

  } else if (strcmp(token, ";") == 0) {
    stoken.type = TypeSemiColon;
  } else if (checkString(token)) {
    stoken.type = TypeIdentifier;
  } else if (checkNumber(token)) {
    stoken.type = TypeLiteral;
  } else {
    stoken.type = TypeIllegal;
  }

  return stoken;
}

Token *tokenizer(char **stream, Token *tokens) {
  int i = 0;
  while (*stream != NULL) {
    tokens[i] = tokenIdentifier(*stream);
    i++;
    stream++;
  }
  return tokens;
}
