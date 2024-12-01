/* lexer.c */

#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>

void display(Token *tokens);

void generate_keyword(Token *tokens, char **str, TokenKind kind) {
  int j = 0;
  char buff[10] = "";
  char *str_ptr = *str;

  while (**str == '-' || isalpha(**str)) {
    buff[j] = **str;
    (*str)++;
    j++;
  }
  tokens->cmd = malloc(sizeof(char) * j);
  strncpy(tokens->cmd, str_ptr, j);
  tokens->kind = kind;
}

void lexer(char *input, Token **tokens) {

  if (isalpha(*input)) {
    generate_keyword(*tokens, &input, COMMAND);
    (*tokens)++;
    while (isspace(*input)) {
      input++;
    }
    if (*input == '-' && isalpha(*(input + 1))) {
      generate_keyword(*tokens, &input, OPTIONS);
      (*tokens)++;
    }
    while (isspace(*input)) {
      input++;
    }
    if (isalpha(*input)) {
      generate_keyword(*tokens, &input, ARGUMENTS);
      (*tokens)++;
    }
  } else {
    printf("[exotish] : command < %s > not found!!\n", input);
  }
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
