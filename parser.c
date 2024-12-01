#include "parser.h"
#include "lexer.h"

void parse(Token *tokens) {
  if (tokens->kind != END_CMD) {
    char *command = NULL;
    char *options = NULL;
    char *argument = NULL;
    char *argv[4] = {NULL, NULL, NULL, NULL};
    char full_cmd[10] = "/bin/";

    if (tokens->kind == COMMAND) {
      command = (char *)malloc(sizeof(char) * 10);
      strcpy(command, (tokens)->cmd);
      strcat(full_cmd, command);
      argv[0] = full_cmd;
      if ((tokens + 1)->kind == OPTIONS) {
        options = (char *)malloc(sizeof(char) * 10);
        strcpy(options, (tokens + 1)->cmd);
        argv[1] = options;
        if ((tokens + 2)->kind == ARGUMENTS) {
          strcpy(argument, (tokens + 1)->cmd);
          argv[2] = argument;
        }
      } else if ((tokens + 1)->kind == ARGUMENTS) {
        argument = (char *)malloc(sizeof(char) * 10);
        strcpy(argument, (tokens + 1)->cmd);
        argv[1] = argument;
      }
    }

    int ps_child = fork();
    if (!ps_child) {
      int return_execve = execve(argv[0], argv, NULL);
      if (return_execve == -1)
        printf("[exotish] : command <%s> not found!!\n", tokens->cmd);
    }
    wait(NULL);
  }
}
