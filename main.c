#include "lexer.h"

int main() {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen = 1;

  while (1) {
    write(STDOUT_FILENO, "exotish~$ ", 9);
    linelen = getline(&line, &linecap, stdin) - 1;
    line[linelen] = '\0';
    lexer(line, linelen);
  }
  return 0;
}
