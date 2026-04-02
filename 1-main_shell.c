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
 * main - do the job
 * @ac: number of arguments
 * @av: arguments
 * @env: environment variables
 * Return: always 0
 */

int main(void)
{
	char **prompt_command = NULL, **path_directories = NULL;
	int prompt_args = 0, how_many_dir_in_path = 0, dir_lenght = 0, i = 0;
	char *buff = NULL;
	struct stat st;

	prompt_command = clean_getline();
	free_and_exit_null_prompt(prompt_command);
	for (i = 0; prompt_command[0] != NULL; i++)
	{
	prompt_args = array_lenght(prompt_command);
	exit_if_more_than_two(prompt_args);
	path_directories = get_clean_path_directories();
	how_many_dir_in_path = array_lenght(path_directories);
		for (i = 0; i < how_many_dir_in_path; i++)
		{
			dir_lenght = get_dir_lenght(path_directories[i], prompt_command[0]);
			buff = malloc(sizeof(char) * dir_lenght);
			if (buff == NULL)
			{
				return (-1);
			}
			snprintf(buff, dir_lenght, "%s/%s", path_directories[i], prompt_command[0]);
			if (stat(buff, &st) == 0)
			{
				fork_and_launch(buff, prompt_command);
				free_everything(buff, prompt_command, path_directories);
				prompt_command = clean_getline();
				free_and_exit_null_prompt(prompt_command);
				break;
			}
			free(buff);
		}
	}
	return (0);
}
