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
	char *lineptr = NULL;
	int return_code = 40;
	int zero = argc - argc;
	char *shell_name = av[zero];
	int build_in_status = 0;

	prompt_command = clean_getline(&lineptr);

	for (i = 0; prompt_command != NULL; i++)
	{
		if (prompt_command[0] != NULL)
		{
		/* --- VOIE 1 : Est-ce un Built-in ? --- */
			build_in_status = is_build_in(prompt_command);
			if (build_in_status != 127)
			{
				/* On passe la note précédente pour que exit puisse s'en servir */
				return_code = build_in_centralizer(build_in_status, prompt_command, lineptr, return_code);
			}
			/* --- VOIE 2 : SINON, est-ce un chemin absolu (/ ou .) ? --- */
			else if (prompt_command[0][0] == '/' || prompt_command[0][0] == '.')
			{
				return_code = launch_with_dir(prompt_command);
			}
			/* --- VOIE 3 : SINON, c'est une commande classique dans le PATH --- */
			else
			{
				/* On récupère le PATH SEULEMENT si on en a besoin ici ! */
				path_directories = get_clean_path_directories(__environ);
				hm_dir_in_path = array_lenght(path_directories);
				
				if (path_directories != NULL)
				{
					return_code = launch_with_command(hm_dir_in_path, prompt_command, path_directories);
				}
				else
				{
					/* Si le PATH a été supprimé (env -i), on force l'erreur */
					return_code = 127; 
				}
			}

			/* --- GESTION DES ERREURS --- */
			/* Si on a pris la bonne voie mais que la commande est introuvable */
			if (return_code == 127 || return_code == -1)
			{
				return_code = print_error_message(shell_name, prompt_command, i + 1);
			}
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


