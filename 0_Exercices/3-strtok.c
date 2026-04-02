#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



int main(void)
{
	char **array=NULL;
	char test_string[] = "New test for the string I'm trying to test testy testy test";
	int lenght = 0;
	int i = 0;

	for (i = 0; *(test_string + i) != '\0'; i++)
	{
		if (*(test_string + i) == ' ')
		{
			lenght++;
		}
	} 

	lenght = lenght + 1;
	i = 0;
	array = malloc (sizeof(char *)* lenght);
	if (array == NULL)
	{
		return (-1);
	}

	array[i] = strtok(test_string, " ");

	for (i = 1; i < lenght; i++)
	{
		array[i] = strtok(NULL, " ");
	}

	for (i = 0; i < lenght; i++)
	{
		printf("Array %d : %s\n", i, array[i]);
	}
	
	free(array);

	return (0);

}