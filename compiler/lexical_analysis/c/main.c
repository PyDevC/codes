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
        return 1;
      mainfile->f = fopen(argv[1], "r");
      mainfile->c = 0;
      mainfile->n = 0;
      char *reader = malloc(BUFSIZE * sizeof(char));
      if (reader == NULL)
        return 1;
      while (fgets(reader, BUFSIZE, mainfile->f) != NULL) {
        mainfile->n++;
        printf("%s", reader);
      }
      fclose(mainfile->f);
      free(reader);
      free(mainfile);
      return 0;
    } else {
      perror("File does not exists");
      return 1;
    }
  }
}
