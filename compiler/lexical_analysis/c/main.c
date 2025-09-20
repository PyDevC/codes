#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **streamer(FILE *source) {
  char currentchar;
  size_t token_capacity = 1024;
  size_t token_length = 0;
  char *token = malloc(token_capacity);

  size_t stream_capacity = 8;
  size_t token_counter = 0;
  char **stream = malloc(stream_capacity * sizeof(token));

  while ((currentchar = fgetc(source)) != EOF) {
    if (currentchar == ' ' && token_length > 0) {
      if (token_counter >= stream_capacity - 1) {
        stream_capacity *= 2;
        char **temp = realloc(stream, stream_capacity * sizeof(char *));
        stream = temp;
      }

      token[token_length] = '\0';

      stream[token_counter] = strdup(token);
      if (stream[token_counter] == NULL) {
        perror("Failed to duplicate token string");
        for (size_t i = 0; i < token_counter; i++) {
          free(stream[i]);
        }
        free(stream);
        free(token);
        return NULL;
      }
      token_length = 0;
      token[0] = '\0';
      token_counter++;
      continue;
    }

    if (token_length + 1 >= token_capacity) {
      token_capacity *= 2;
      char *temp = realloc(token, token_capacity);
      if (temp == NULL) {
        perror("Failed to reallocate token buffer");
        for (size_t i = 0; i < token_counter; i++) {
          free(stream[i]);
        }
        free(stream);
        return NULL;
      }
      token = temp;
    }

    token[token_length] = currentchar;
    token_length++;
  }

  if (token_length > 0) {
    if (token_counter >= stream_capacity - 1) {
      stream_capacity++;
      char **temp = realloc(stream, stream_capacity * sizeof(token));
      if (temp == NULL) {
        perror("Failed to reallocate stream for final token");
        free(stream);
        free(token);
        return NULL;
      }
      stream = temp;
    }
    token[token_length] = '\0';
    stream[token_counter] = strdup(token);
    if (stream[token_counter] == NULL) {
      perror("Failed to duplicate final token string");
      free(stream);
      free(token);
      return NULL;
    }
    token_counter++;
  }
  free(token);
  if (token_counter >= stream_capacity) {
    stream_capacity++;
    stream = realloc(stream, stream_capacity * sizeof(char *));
  }
  stream[token_counter] = NULL;

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
  Token *tokens = malloc(8 * sizeof(Token));
  tokens = tokenizer(out, tokens);
  int i;
  for (i = 0; i < 8; i++) {
    printf("%d ", tokens->type);
    tokens++;
  }
  return 0;
}
