#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Declare the environ variable */
extern char **environ;

/* Function prototypes */
char *read_input(void);
char **parse_input(char *input, int *argc);
int validate_command(char **argv);
void execute_command(char **argv);
char *gettingThePath(char *arg);

#endif
