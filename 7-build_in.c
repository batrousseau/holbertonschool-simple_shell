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
 * is_build_in - Analyse if the command passed through the terminal
 * is a build in
 * @prompt_command: array of command
 * Return : 127 if not build_in or NULL, 1 if exit, 2 if env
 */

int is_build_in(char **prompt_command)
{
	char *exit = "exit";
	char *env = "env";
	int exit_result = -1;
	int env_result = -1;
	

	if (prompt_command == NULL || prompt_command[0] == NULL)
	{
		return (127);
	}
	
	exit_result = _strcmp(exit, prompt_command[0]);

	if (exit_result == 0)
	{
		return (1);
	}
	
	env_result = _strcmp(env, prompt_command[0]);

	if (env_result == 0)
	{
		return (2);
	}

	return(127);
}

/**
 * build_in_centralizer - calls the proper function
 * depending on what int it receives
 * @build_int : an int indicating the code
 * Return: Nothing
 * */

int build_in_centralizer(int build_int, char **prompt_command, char *lineptr, int actual_return)
{
	int exit_return = 0;
	int env_return = 0;

	if(build_int == 127)
	{
		return (0);
	}

	if (build_int == 1 && prompt_command != NULL && lineptr != NULL)
	{
		exit_return = exit_build_in(prompt_command, lineptr, actual_return);
		return (exit_return);
	}

	if (build_int == 2)
	{
		env_return = env_build_in();
		return (env_return);
	}
	
return (127);
}

/** exit_build_in - exit function
 * Return: Nothing for the moment
 */

int exit_build_in(char **prompt_command, char *lineptr, int actual_return)
{
int status_arg = 0;

/* if there's an argument to exit I must catch it as return*/
if (prompt_command[1] != NULL && prompt_command[1][0] != '\0')
{
	/* if it's only one number, let's strore it*/
	status_arg = prompt_command[1][0] - 48;
	if (prompt_command[1][1] != '\0')
	{
		/* if there is two number I must convert it */
		status_arg = status_arg * 10 + (prompt_command[1][1] - 48);
	}
}

else
{
	status_arg = actual_return;
}

free(prompt_command);
free(lineptr);
exit(status_arg);
}

/**
 * env_build_in - env function
 * Return: Nothing for the moment
 */

int env_build_in()
{
	if(__environ == NULL && __environ[0] != NULL)
	{
		return (127);
	}
	print_array(__environ);
	return(0);
}