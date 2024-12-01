#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main() {
  Token *tokens;
  Token *tokens_ptr;
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen = 1;

  while (1) {
    tokens = (Token *)malloc(sizeof(Token) * 4);
    tokens_ptr = tokens;
    write(STDOUT_FILENO, "exotish~$ ", 9);
    linelen = getline(&line, &linecap, stdin) - 1;
    line[linelen] = '\0';

    lexer(line, &tokens);
    tokens->kind = END_CMD;
    //    display(tokens_ptr);
    parse(tokens_ptr);
  }
  return 0;
}
