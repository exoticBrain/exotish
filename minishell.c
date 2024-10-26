#include "minishell.h"

int main(int argc, char *argv[]) {

  (void)argc;
  (void)argv;
  /*
    if (argc != 2) {
      printf("[exotish] : syntax error %s command\n", argv[0]);
      return (1);
    }

   */
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen = 1;
  char *av[] = {"/bin/", NULL};

  while (linelen > 0) {
    write(STDOUT_FILENO, "exotish~$ ", 9);
    linelen = getline(&line, &linecap, stdin) - 1;
    line[linelen] = '\0';
    printf("cmd : %s\n", line);

    if (strcmp(line, "exit") == 0) {
      write(STDOUT_FILENO, "EXITING THE SHELL!!\n", 20);
      exit(EXIT_FAILURE);
    }

    // av[0] = (char *)malloc(sizeof(char) * linelen);
    strncat(av[0], line, linelen);
    int ps_child = fork();
    if (!ps_child) {
      execve(line, av, NULL);
    }
    wait(NULL);
  }
  free(av[0]);
  return 0;
}
