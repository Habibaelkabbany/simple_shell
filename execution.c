#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "main.h"

/**
 * execute_command - Execute the command
 *
 * @argv: The array of arguments
 */
void execute_command(char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		wait(NULL);
	}
}

