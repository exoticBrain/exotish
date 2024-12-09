#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (strcmp(line, "") != 0) {
      if (strcmp(line, "clear") == 0) {
        system("clear");
      } else if (strcmp(line, "exit") == 0) {
        printf("EXITING EXOTISH -----\n");
        exit(EXIT_FAILURE);
      } else {
        lexer(line, &tokens);
        if (strcmp(tokens_ptr->cmd, "cd") == 0) {
          if ((tokens_ptr + 1)->kind == ARGUMENTS) {
            chdir((tokens_ptr + 1)->cmd);
          } else if ((tokens_ptr + 1)->kind == END_CMD) {
            chdir("/Users/exotic");
          }
          continue;
        }
        // display(tokens_ptr);
        parse(tokens_ptr);
      }
    }
  }
  return 0;
}
