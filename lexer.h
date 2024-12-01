#ifndef LEXER_H

#define LEXER_H

#include "shell.h"
#include <ctype.h>

typedef enum { COMMAND, PIPE, OPTIONS, ARGUMENTS, END_CMD, } TokenKind;

typedef struct {
  char *cmd;
  TokenKind kind;
} Token;

void lexer(char *input, Token **tokens);
void display(Token *tokens);

#endif // LEXER_H
