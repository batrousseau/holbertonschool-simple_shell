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
 * _strdup - copy a string
 * @str: a string
 * Return: pointer to a copy of the
 * string
 */
char *_strdup(char *str)
{
int i = 0;
int lenght = 0;
char *s;

if (str == NULL)
{
return (NULL);
}


for (i = 0; *(str + i) != '\0'; i++)
{
}
lenght = i + 1;

s = malloc(lenght * 1);

if (s == NULL)
{
return (NULL);
}

for (i = 0; i < lenght; i++)
{
*(s + i) = *(str + i);
}


return (s);
}

/**
* free_array - frees a 2 dimensional integer grid
* previously created by alloc_grid
* @grid: the 2 dimensionnal array
* Return: Nothing
*/

void free_array(char **grid)
{
int i = 0;
int height = 0;

if (grid == NULL || *grid == NULL)
{
	return;
}
/* Getting height */
for (i = 0; *(grid + i) != NULL; i++)
{
}
height = i;

for (i = 0; i < height; i++)
{
free(grid[i]);
}
free(grid);
grid = NULL;
}

/**
 * get_strlenght - get string
 * lenght
 * @s: a string
 * Return: number of char in the string
 */
int get_strlenght(char *s)
{
	int i = 0;
	int result = 0;

	if (s == NULL)
	{
		return (-1);
	}
	for (i = 0; *(s + i) != '\0'; i++)
	{
	}
	result = i;

	return (result);

}

/**
 * count_double_dot - count the double dot
 * inside PATH env variable to help shell tools
 * prepare a good array of directories
 * @s: string containing PATH
 * Return: number of directories deduced by
 * double_dots
 */
int count_double_dot(char *s)
{

	int i = 0;
	int result = 0;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		if (*(s + i) == ':')
		{
			result = result + 1;
		}
	}
	result = result + 1;
	return (result);
}
/**
 * array_lenght - count how many cell are in
 * the array
 * @array: the array to count
 * Return: number of cells
 */
int array_lenght(char **array)
{
	int i = 0;
	int cells_number = 0;

	if (array == NULL || *array == NULL)
	{
		return (-1);
	}

	for (i = 0; *(array + i) != NULL; i++)
	{
	}
	cells_number = i + 1;
	return (cells_number);
}

