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
 * get_path_from_env - take environ constant
 * and look for the path. Then return the beginning
 * of
 */

char *get_path_from_env(char **env)
{
	int i = 0;
	int j = 0;
	char *s = NULL;
	char *clean_path = NULL;

	if (env[0] == NULL)
	{
		return(NULL);
	}
	
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
if (clean_path == NULL || clean_path[0] == '\0')
{
	return(NULL);
}

return(clean_path);
}
