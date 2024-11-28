#ifndef LEXER_H

#define LEXER_H

#include "shell.h"
#include <ctype.h>

typedef enum {
    COMMAND,
    PIPE,
    ARGUMENTS_CMD,
} TokenKind;

typedef struct {
    char *cmd;
    TokenKind kind;
} Token;

void lexer(char *input);

#endif // LEXER_H

