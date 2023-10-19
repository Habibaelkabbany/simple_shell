#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL;
	char **argv = NULL;
	int argc = 0;

	while (1)
	{
		input = read_input();
		if (input == NULL)
		{
			exit(EXIT_SUCCESS);
		}
		argv = parse_input(input, &argc);

		if (validate_command(argv) == 0)
		{
			execute_command(argv);
			free(argv);
			free(input);
		}
	}
	return (0);
}

/**
 * read_input - Read user input from stdin
 *
 * Return: Pointer to the input string
 */
char *read_input(void)
{
	char *input = NULL;
	size_t n = 0;

	printf("$$  ");
	if (getline(&input, &n, stdin) == -1)
	{
		if (feof(stdin))
			return (NULL);
		perror("Failed to read input");
		exit(EXIT_FAILURE);
	}
	return (input);
}

/**
 * parse_input - Parse the input string into an array of arguments
 *
 * @input: The input string
 * @argc: Stores the number of arguments
 *
 * Return: Pointer to the array of arguments
 */
char **parse_input(char *input, int *argc)
{
	char *token = NULL;
	char *delim = " \n";
	char **argv = NULL;
	int i = 0;
	char *incopy = NULL;

	incopy = strdup(input);
	token = strtok(input, delim);

	while (token)
	{
		token = strtok(NULL, delim);
		(*argc)++;
	}
	if (*argc == 0)
	{
		perror("Please enter correct number of args");
		exit(EXIT_FAILURE);
	}
	argv = malloc(sizeof(char *) * (*argc + 1));
	if (argv == NULL)
	{
		perror("Failed to allocate memory for argv");
		exit(EXIT_FAILURE);
	}
	token = strtok(incopy, delim);
	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * validate_command - Validate that the command is executable
 *
 * @argv: The array of arguments
 *
 * Return: 0 on success -1 on failure
 */
int validate_command(char **argv)
{
	argv[0] = gettingThePath(argv[0]);
	/* Validate command */
	if (access(argv[0], X_OK) == -1)
	{
		if (errno == EACCES)
		{
			perror("Permission denied");
		}
		else
		{
			perror("Command not found");
		}
		return (-1);
	}
	return (0);
}

