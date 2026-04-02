#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "shell.h"


char *get_path_from_env(char **env)
{
	int i = 0;
	int j = 0;
	char *s = NULL;
	char *clean_path = NULL;

	for (i = 0; *(env + i) != NULL; i++)
	{
		s = *(env + i);
		for (j = 0; *(s + j) != '\0'; j++)
		{
			if (*(s + j) != 'P')
			{
				break;
			}
			else
			{
				if (*(s + j + 1) != 'A')
				{
					break;
				}
				else
				{
					clean_path = (s + 5);
				}
				
			}
			
		}
	}
return(clean_path);
}
