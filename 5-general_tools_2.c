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
/* On nettoie la ligne d'origine (free(NULL) ne fait rien, c'est safe) */
	free(buff);
	
	/* On nettoie le tableau découpé par strtok */
	if (prompt != NULL)
	{
		free(prompt);
	}

	/* Le fameux bouclier anti-segfault pour le PATH */
	if (dir_path != NULL)
	{
		free(*dir_path); 
/* Maintenant on est SÛR que dir_path n'est pas NULL, on peut utiliser l'étoile ! */
		free(dir_path);
	}
}

/**
 * print_error_message - handle message error
 * @prompt: command line taped by user
 * @loop_count: how many commands entered in the shell
 * Return : 127 because error
 */

int print_error_message(char *shell_name, char **command, int loop_count)
{
	if (command == NULL || shell_name == 0)
	{
		return (0);
	}
	fprintf(stderr, "%s: %d: %s: not found\n", shell_name, loop_count, command[0]);
	return(127);
}
