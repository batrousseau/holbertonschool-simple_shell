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
 * @path_directories: array of pathdir
 * Return: nothing
 */
void free_and_exit_null_prompt(char **prompt, char **path_directories)
{
if (prompt == NULL || prompt[0] == NULL)
	{
/* Si on détecte un Ctrl+D (EOF) */
	if (prompt == NULL || prompt[0] == NULL)
	{
		/* On nettoie le prompt s'il reste des miettes de getline */
		if (prompt != NULL)
		{
			free(prompt); /* Ou ta fonction spécifique pour free le prompt */
		}

		/* 🚨 C'est ICI qu'on règle ton dernier bug Valgrind ! 🚨 */
		/* Grâce au "= NULL" qu'on a mis dans le main, on sait si on doit free ou pas */
		if (path_directories != NULL)
		{
			free(*path_directories); /* Détruit la grosse chaîne de 1032 bytes */
			free(path_directories);  /* Détruit le tableau de 240 bytes */
		}

		/* On ferme le programme ! */
		exit(EXIT_SUCCESS);
	}
	}
}
