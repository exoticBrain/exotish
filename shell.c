#include "shell.h"

/*
int main() {

(void)argc;
(void)argv;
if (argc != 2) {
  printf("[exotish] : syntax error %s command\n", argv[0]);
  return (1);
}

char *line = NULL;
size_t linecap = 0;
ssize_t linelen = 1;

while (1) {
  write(STDOUT_FILENO, "exotish~$ ", 9);
  linelen = getline(&line, &linecap, stdin) - 1;
  line[linelen] = '\0';

  if (strcmp(line, "exit") == 0) {
    write(STDOUT_FILENO, "EXITING THE SHELL!!\n", 20);
    exit(EXIT_FAILURE);
  } else if (strcmp(line, "clear") == 0) {
    system("clear");
    continue;
  } else {
    char *command[] = {NULL, NULL};
    size_t full_cmd_size = linelen + BIN_PATH_LEN + 1;

    command[0] = (char *)malloc(sizeof(char) * full_cmd_size);
    strcpy(command[0], BIN_PATH);
    strlcat(command[0], line, full_cmd_size);
    printf("cmd: %s\n", command[0]);
    int ps_child = fork();
    if (!ps_child) {
      int return_execve = execve(command[0], command, NULL);
      if (return_execve == -1)
        printf("[exotish] : command <%s> not found!!\n", line);
    }
    wait(NULL);
    free(command[0]);
  }
}
return 0;
}
*/
