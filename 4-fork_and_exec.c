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
 * free_everything - multiples free in one fonction
 * to optimize main shell
 * @buff: buffer for the program absolute directory
 * @prompt: array of args
 * @dir_path: all directories in the path
 */

void free_everything(char *buff, char **prompt, char **dir_path)
{
	free(buff);
	free(*prompt);
	free(prompt);
	free(*dir_path);
	free(dir_path);
}


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
		perror("Error:");
		return (-1);
		}
	}
	else
	{
		wait(&status);
	}
return (0);
}
