/* lexer.c */

#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **generate_tokens(char *input, size_t *number_of_tokens);
void display(Token *tokens);
void display_tokens_lexer(char **tokens);
void parse_token(Token **tokens, char **tokens_generated, TokenKind kind,
                 size_t token_idx) {
  size_t len_current_token = 0;

  len_current_token = strlen(tokens_generated[token_idx]);
  (*tokens)->cmd = malloc(sizeof(char) * len_current_token);
  strcpy((*tokens)->cmd, tokens_generated[token_idx]);
  (*tokens)->kind = kind;
  (*tokens)++;
}

void lexer(char *input, Token **tokens) {
  size_t number_of_tokens = 0;
  char **tokens_generated = generate_tokens(input, &number_of_tokens);

  if (number_of_tokens) {
    parse_token(tokens, tokens_generated, COMMAND, 0);
    switch (number_of_tokens) {
    case 2:
      if (tokens_generated[1][0] == '-') {
        parse_token(tokens, tokens_generated, OPTIONS, 1);
      } else {
        parse_token(tokens, tokens_generated, ARGUMENTS, 1);
      }
      break;
    case 3:
      parse_token(tokens, tokens_generated, OPTIONS, 1);
      parse_token(tokens, tokens_generated, ARGUMENTS, 2);
      break;
    }
    (*tokens)->kind = END_CMD;
  }
}

char **generate_tokens(char *input, size_t *lnegth) {

  char *input_copy = strdup(input);
  char *delim = " ";
  char *token;
  int i = 0;
  char **av;

  for (token = strtok(input_copy, delim); token != NULL;
       token = strtok(NULL, delim)) {
    i++;
  }

  free(input_copy);
  av = malloc(sizeof(char *) * (i + 1));
  if (av == NULL) {
    perror("Error allocating memory");
    exit(EXIT_FAILURE);
  }
  av[i] = NULL;

  for (token = strtok(input, delim); token != NULL;
       token = strtok(NULL, delim)) {
    av[*lnegth] = token;
    (*lnegth)++;
  }
  return av;
}

void display(Token *tokens) {
  while (tokens->kind != END_CMD) {
    printf("Token : ");

    switch (tokens->kind) {
    case COMMAND:
      printf("[Command] ");
      break;
    case PIPE:
      printf("[PIPE] ");
      break;
    case ARGUMENTS:
      printf("[ARGUMENTS] ");
      break;
      break;
    case OPTIONS:
      printf("[OPTIONS] ");
      break;
    case END_CMD:
      printf("[END_CMD] ");
      break;
    }
    if (tokens->kind != END_CMD)
      printf("VALEUR : %s\n", tokens->cmd);
    tokens++;
  }
}

void display_tokens_lexer(char **tokens) {
  while (*tokens) {
    printf("Token : %s\n", *tokens);
    tokens++;
  }
}
