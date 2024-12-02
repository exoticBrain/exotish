#include "parser.h"
#include "lexer.h"

void parse(Token *tokens) {
  if (tokens->kind != END_CMD) {
    char *options = NULL;
    char *argument = NULL;
    char *argv[4] = {NULL, NULL, NULL, NULL};

    if (tokens->kind == COMMAND) {
      char command[256];
      char path[256]; // Buffer to store the output

      // Construct the command string
      snprintf(command, sizeof(command), "which %s", tokens->cmd);

      // Open a pipe to read the command's output
      FILE *fp = popen(command, "r");
      if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
      }

      // Read the output of the command
      if (fgets(path, sizeof(path), fp) != NULL) {
        // Remove the newline character at the end of the string, if present
        path[strcspn(path, "\n")] = '\0';
        // Close the pipe
        pclose(fp);

        strcpy(command, (tokens)->cmd);
        argv[0] = path;
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
    }

    int ps_child = fork();
    if (!ps_child) {
      int return_execve = execve(argv[0], argv, NULL);
      if (return_execve == -1) {
        printf("\n");
        perror("[exotish]");
        printf("Command <%s> not found!!\n", tokens->cmd);
      }
    }
    wait(NULL);
  }
}
