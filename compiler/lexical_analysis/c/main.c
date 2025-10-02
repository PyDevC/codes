#include "lexer.h"
#include <stdio.h>

int main(void) {
  char *source_code[] = {"local", "a", "=", "\"This is\""};
  SToken *TokenList = Tokenizer(source_code);
  int i;
  for (i = 0; i < 4; i++) {
    printf("%d ", TokenList[i].Tokentype);
  }
  return 0;
}
