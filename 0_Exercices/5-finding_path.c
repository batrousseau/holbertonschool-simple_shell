#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

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
	return result;
}

int get_strlenght(char *s)
{
	int i = 0;
	int result = 0;

	for (i = 0; *(s + i) != '\0';i++)
	{
	}
	result = i;
	
	return(result);

}

int main(int ac, char **av)
{
struct stat st;
char *path = NULL;
int array_lenght = 0;
char **env = NULL;
char *buff = NULL;
int dir_lenght = 0;
int i = 0;


if (ac < 2)
{
	printf("Not enough args\n");
	return(-1);
}

path = getenv("PATH");
array_lenght = count_double_dot(path);
env = malloc(sizeof(char *) * array_lenght);
if (env == NULL)
{
	return (-1);
}

env[i] = strtok(path, ":");

for (i = 1; i < array_lenght; i++)
{
	env[i] = strtok(NULL, ":");
}

for (i = 0; i < array_lenght; i++)
{
	dir_lenght = get_strlenght(env[i]) + get_strlenght(av[1]) + 2;
	buff = malloc(sizeof(char) * dir_lenght);
	if (buff == NULL)
	{
		return(-1);
	}
	snprintf(buff,dir_lenght,"%s/%s", env[i],av[1]);
	if (stat(buff,&st) == 0)
	{
		printf("%s exist in %s\n", av[1], buff);
	}	
	free(buff);
	
}


free(env);

return(0);
}
