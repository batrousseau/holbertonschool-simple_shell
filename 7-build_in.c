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
	

	if (prompt_command[0] == NULL)
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

int build_in_centralizer(int build_int)
{
	int exit_return = 0;
	int env_return = 0;

	if(build_int == 127)
	{
		return (0);
	}

	if (build_int == 1)
	{
		exit_return = exit_build_in();
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

int exit_build_in()
{
 exit(EXIT_SUCCESS);
}

/**
 * env_build_in - env function
 * Return: Nothing for the moment
 */

int env_build_in()
{
	if(__environ == NULL)
	{
		return (127);
	}
	print_array(__environ);
	return(0);
}