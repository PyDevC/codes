#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **streamer(FILE *source) {
  char currentchar;
  size_t token_capacity = 128;
  size_t token_length = 0;
  char *token = malloc(token_capacity);

  size_t stream_capacity = 1024;
  char **stream = malloc(8 * sizeof(*token));
  token[0] = '\0';

  char WHITESPACE = ' ';
  int token_counter = 0;
  while ((currentchar = fgetc(source)) != EOF) {
    if (currentchar == WHITESPACE && token_length > 0) {
      printf("%s\n", token);
      token[0] = '\0';
      token_length = 0;
      stream[token_counter] = token;
      continue;
    }
    if (token_length + 2 >= token_capacity) {
      token_capacity *= 2;
      token = realloc(token, token_capacity);
    }
    token[token_length] = currentchar;
    token_length++;
    token[token_length] = '\0';
  }
  stream[7] = NULL;
  return stream;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No source code provided");
    return 1;
  }
  FILE *source;
  source = fopen(argv[1], "r");
  if (source == NULL) {
    printf("File %s does not exists", argv[1]);
    return 1;
  }
  char **out = streamer(source);
  while (*out != NULL) {
    printf("%s\n", *out);
    out++;
  }
  return 0;
}
