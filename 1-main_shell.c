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
extern char **__environ;

int main(int argc, char **av)
{
	char **prompt_command = NULL, **path_directories = NULL;
	int hm_dir_in_path = 0, i = 0;
	int absolute_stat = 127, command_stat = 127;
	char *lineptr = NULL;
	int return_code = 0;
	int zero = argc - argc;
	char *shell_name = av[zero];

	
	prompt_command = clean_getline(&lineptr);
	
	for (i = 0; prompt_command != NULL; i++)
	{
		return_code = 0;
		if (prompt_command[0] != NULL)
		{
			path_directories = get_clean_path_directories(__environ);
			hm_dir_in_path = array_lenght(path_directories);
			absolute_stat = launch_with_dir(prompt_command);
			if (absolute_stat == -1 && path_directories != NULL)
			{
				command_stat = launch_with_command(hm_dir_in_path, prompt_command, path_directories);
			}
		}
		if (absolute_stat != 0 && command_stat != 0)
		{
			return_code = print_error_message(shell_name, prompt_command, i);
		}
	free_everything(lineptr, prompt_command, path_directories);
	lineptr = NULL;
	path_directories = NULL;
	prompt_command = clean_getline(&lineptr);
	}
	free(lineptr);
	lineptr = NULL;
	return (return_code);
}


