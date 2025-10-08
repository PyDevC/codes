#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

static int readable(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return 0;
  fclose(file);
  return 1;
}

typedef struct ReaderF {
  unsigned n; // linenumber
  unsigned c; // colnumber
  FILE *f;
} ReaderF;

int main(int argc, char **argv) {
  if (argc == 2) {
    if (readable(argv[1])) {
      ReaderF *mainfile = (ReaderF *)malloc(sizeof(ReaderF));
      if (mainfile == NULL)
        return EXIT_FAILURE;
      mainfile->f = fopen(argv[1], "r");
      mainfile->c = 0;
      mainfile->n = 0;
      char *reader = malloc(BUFSIZE * sizeof(char));
      SToken *TokenList = (SToken *)malloc(BUFSIZE * sizeof(SToken));
      int TokenListIdx = 0;
      if (reader == NULL)
        return EXIT_FAILURE;
      while (fgets(reader, BUFSIZE, mainfile->f) != NULL) {
        Tokenizer(TokenList, TokenListIdx, reader);
        mainfile->n++;
      }
      // Closing and freeing everything in main
      fclose(mainfile->f);
      free(reader);
      free(mainfile);
      free(TokenList);
      return EXIT_SUCCESS;
    } else {
      perror("File does not exists");
      return EXIT_FAILURE;
    }
  }
  return EXIT_FAILURE;
}
