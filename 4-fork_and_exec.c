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
 * fork_and_launch - manage the child process of the shell
 * @path: complete directory in which to find the program
 * @prompt: arguments of the command line
 * Return: -1 if error, or 0 if all right
 */

int fork_and_launch(char *path, char **prompt)
{
	__pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error\n");
	}
	if (child_pid == 0)
	{
		if (execve(path, prompt, NULL) == -1)
		{
		perror("Error");
		return (-1);
		}
	}
	else
	{
		wait(&status);
	}
return (0);
}

/**
 * launch_with_dir - launch a command when the
 * prompt is the absolute value of a dir
 * @path_numbers: number of directory to compare the 
 * absolute value to
 * @prompt_commands: array of commands from the prompt
 * Return: nothing
 */

void launch_with_dir(int path_numbers, char **prompt)
{
	int i = 0;
	struct stat st;

	if ( *(*prompt + i) != '/')
	{
		return;
	}

	for (i = 0; i < path_numbers; i++)
	{
		if (stat(prompt[i], &st) == 0)
			{
				
				fork_and_launch(prompt[i], prompt);
				free(*prompt);
				free(prompt);
				prompt = clean_getline();
				free_and_exit_null_prompt(prompt);
				break;
			}
	}

}