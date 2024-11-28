/* lexer.c */

#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>

void lexer(char *input, int length) {
  Token *tokens;
  char buff[10];
  int j;

  tokens = (Token *)malloc(sizeof(Token));
  for (int i = 0; i < length; i++) {
    j = 0;
    bzero(buff, 10);
    if (isalpha(input[i])) {
      while (isalpha(input[i])) {
        buff[j] = input[i];
        i++;
        j++;
      }
      *tokens = generate_cmd(buff);
      printf("the command is :\t%s\n", buff);
      i--;
    } else if (isspace(input[i])) {
      printf("Found space\n");
    } else {
      printf("[LEXER] Syntax error: \n");
      exit(EXIT_FAILURE);
    }
  }
}
