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
	int real_status;

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
		if (WIFEXITED(status))
		{
			/* 2. On extrait le VRAI code renvoyé par le programme (ex: 0, 2, 127) */
			real_status = WEXITSTATUS(status);
			
			/* 3. On le renvoie au main ! */
			return (real_status);
		}
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

int launch_with_dir(char **prompt)
{
	int i = 0;
	int j = 0;
	int status = 127;
	struct stat st;

	if ( *(prompt[j]) != '/' && *(prompt[j]) != '.')
	{
		return (-1);
	}

	if (stat(prompt[i], &st) == 0)
	{
		status = fork_and_launch(prompt[i], prompt);
	}
	
return (status);
}

/**
 * launch_with_command - take arg of the prompt and build
 * the absolute path
 */

int launch_with_command(int how_many_dir_in_path, char **prompt_command, char **path_directories)
{
	char *buff = NULL;
	int j = 0;
	int dir_lenght = 0;
	struct stat st;
	int status = 127;

	for (j = 0; j < how_many_dir_in_path; j++)
	{
		dir_lenght = get_dir_lenght(path_directories[j], prompt_command[0]);
		buff = malloc(sizeof(char) * dir_lenght);
		if (buff == NULL)
		{
			return (-1);
		}
		snprintf(buff, dir_lenght, "%s/%s", path_directories[j], prompt_command[0]);
		if (stat(buff, &st) == 0)
		{
			status = fork_and_launch(buff, prompt_command);
			free(buff);
			break;
		}
	free(buff);
	}

	return (status);
}

