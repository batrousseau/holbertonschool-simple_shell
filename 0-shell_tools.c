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
 * stroke_getline - transform the string
 * passed as command into an array of strings
 * @command_line: the command line from
 * clean_getline function
 * Return: array of args
 */

char **stroke_getline(char *command_line)
{
int lenght = 0;
int i = 0;
char **array = NULL;

/* First we need to know the number of args contained in the string*/
for (i = 0; *(command_line + i) != '\0'; i++)
{
	if (*(command_line + i) == ' ')
	{
		lenght++;
	}
}
lenght = lenght + 2;

/* We allocate the right number of args*/
i = 0;
array = malloc(sizeof(char *) * lenght);
if (array == NULL)
{
	return (NULL);
}
/* We strok each args into the array*/
array[i] = strtok(command_line, " ");

for (i = 1; i < lenght - 1 ; i++)
{
	array[i] = strtok(NULL, " ");
}
array[lenght - 1] = NULL;
return (array);
}

/**
 * no_new_line - change \n with EOL character
 * @impious_line: a string
 * Return: Clean line
*/

char *no_new_line(char *impious_line)
{
	int i = 0;

	if (impious_line == NULL)
	{
		return (NULL);
	}

	for (i = 0; *(impious_line + i) != '\0'; i++)
	{
		if (*(impious_line + i) == '\n')
		{
			*(impious_line + i) = '\0';
		}
	}

	return (impious_line);
}

/**
 * clean_getline - use getline to get
 * command line without \n at the end
 * of the instruction, providing error in
 * the rest of the file and handling and of file case
 * Return: array of args (tks to stroke_getline)
 */

char **clean_getline(void)
{
char *lineptr = NULL;
size_t n = 0L;
int getline_status = 0;
char **args_array = NULL;


/* Print the intro to the prompt*/
printf("Bat2mort$ ");

getline_status = getline(&lineptr, &n, stdin);
/* Handle error and EOF case*/
if (getline_status == -1)
{
	if (ferror(stdin))
	{
		perror("Erreur fatale de lecture");
		free(lineptr);
		exit(EXIT_FAILURE);
	}
	else
	{
		free(lineptr);
		exit(EXIT_SUCCESS);
	}
}

/* Let's clean the line of that bad \n */

lineptr = no_new_line(lineptr);

/* Now let's transform command line into an array*/
args_array = stroke_getline(lineptr);


return (args_array);
}

/**
 * get_clean_path_directories - take PATH
 * variables and split directories to let
 * the main function build a string with commmand line
 * Return: array of directories of the PATH
 */

char **get_clean_path_directories(char **env)
{
	char *original_path = NULL;
	char *path_copy = NULL;
	char **path_directories = NULL;
	int array_lenght = 0;
	int i = 0;

	original_path = get_path_from_env(env);
	path_copy = _strdup(original_path);
	array_lenght = count_double_dot(path_copy);
	path_directories = malloc(sizeof(char *) * (array_lenght + 1));
	if (path_directories == NULL)
	{
		return (NULL);
	}

	path_directories[i] = strtok(path_copy, ":");

	for (i = 1; i < array_lenght; i++)
	{
		path_directories[i] = strtok(NULL, ":");
	}
	path_directories[array_lenght - 1] = NULL;
	return (path_directories);
}

/**
 * get_dir_lenght - get the lenght of the absolute directory
 * in which we aims at finding an executable
 * @s1: first string
 * @s2: second string
 * Return: Number of char and space to insert null byte
 */
int get_dir_lenght(char *s1, char *s2)
{
	int result = 0;
	int s1_lenght = 0;
	int s2_lenght = 0;

	s1_lenght = get_strlenght(s1);
	s2_lenght = get_strlenght(s2);

	result = s1_lenght + s2_lenght + 3;
	return (result);
}
