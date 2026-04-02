#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"

/**
 * exit_if_more_than_two - force exit if args
 * is more than two
 * @args: number of args
 * Return : Nothing
 */

void exit_if_more_than_two(int args)
{
	if (args > 2)
	{
		exit(EXIT_FAILURE);
	}
}

/**
 * free_and_exit_null_prompt - analyse a prompt
 * and if null, free the array and exit
 * @prompt: array of args
 * Return: nothing
 */
void free_and_exit_null_prompt(char **prompt)
{
	if (prompt == NULL)
	{
		free(prompt);
		exit(EXIT_SUCCESS);
	}
}
