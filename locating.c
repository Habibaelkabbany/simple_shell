#include "main.h"

/**
 * gettingThePath - finding the correct path
 *
 * @arg: The command
 *
 * Return: The command and its path
 */
char *gettingThePath(char *arg)
{
	char *finalDest, *cpyFinal, *tokenCom, *fullPath;
	int destlen, i;
	struct stat buffer;

	i = 0;
	finalDest = getenv("PATH");
	if (finalDest)
	{
		cpyFinal = strdup(finalDest);
		destlen = strlen(arg);
		tokenCom = strtok(cpyFinal, ":");
		while (tokenCom != NULL)
		{
			i = strlen(tokenCom);
			fullPath = malloc(destlen + i + 2);
			strcpy(fullPath, tokenCom);
			strcat(fullPath, "/");
			strcat(fullPath, arg);
			strcat(fullPath, "\0");
			if (stat(fullPath, &buffer) == 0)
			{
				free(cpyFinal);
				return (fullPath);
			}
			else
			{
				free(fullPath);
				tokenCom = strtok(NULL, ":");
			}
		}
		free(cpyFinal);
		if (stat(arg, &buffer) == 0)
		{
			return (arg);
		}
		return (NULL);
	}
	return (NULL);
}

