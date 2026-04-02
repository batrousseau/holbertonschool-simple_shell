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
 * print_array - print and array (no shit)
 * @s: an array
 * Return: nothing
 */
void print_array(char **s)
{
	int i = 0;

	if (s == NULL)
	{
		return;
	}

	for (i = 0; *(s + i) != NULL; i++)
	{
		printf("%s\n", *(s + i));
	}
}
