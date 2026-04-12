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
 * @argc: number of arguments
 * @av: arguments
 * Return: always 0
 */

int main(int argc, char **av)
{
	char **prompt_cmd = NULL, **path_dir = NULL;
	int hm_dir_in_path = 0, i = 0, rtn_code = 0, build_stat = 0, zr = argc - argc;
	char *lineptr = NULL, *shell_name = av[zr];
	extern char **__environ;

	prompt_cmd = clean_getline(&lineptr);
	for (i = 0; prompt_cmd != NULL; i++)
	{
		if (prompt_cmd[0] != NULL)
		{
			build_stat = is_build_in(prompt_cmd);
			if (build_stat != 127)
			{
				rtn_code = build_ctrler(build_stat, prompt_cmd, lineptr, rtn_code);
			}
			else if (prompt_cmd[0][0] == '/' || prompt_cmd[0][0] == '.')
			{
				rtn_code = launch_with_dir(prompt_cmd);
			}
			else
			{
				path_dir = get_clean_path_directories(__environ);
				hm_dir_in_path = array_lenght(path_dir);
				if (path_dir != NULL)
				{
					rtn_code = launch_with_command(hm_dir_in_path, prompt_cmd, path_dir);
				}
				else
				{
					rtn_code = 127;
				}
			}
			if (rtn_code == 127 || rtn_code == -1)
			{
				rtn_code = print_error_message(shell_name, prompt_cmd, i + 1);
			}
		}
	free_everything(lineptr, prompt_cmd, path_dir);
	lineptr = NULL;
	path_dir = NULL;
	prompt_cmd = clean_getline(&lineptr);
	}
	free(lineptr);
	lineptr = NULL;
	return (rtn_code);
}


