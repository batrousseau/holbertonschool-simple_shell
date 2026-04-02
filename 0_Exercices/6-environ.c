#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char **__environ;

void print_environ(void)
{
	int i = 0;

	for (i = 0; *(__environ + i) != NULL;i++)
	{
		printf("%s", *(__environ + i));
	}

	return;
}

void print_array(char **s)
{
	int i = 0;

	for (i = 0; *(s + i) != NULL; i++)
	{
		printf("%s\n", *(s + i));
	}
}

int compare_env_key(const char *source, char *to_compare)
{
	int i = 0;

	for (i = 0; *(to_compare + i) != '=';i++)
	{
		if(*(source + i) != *(to_compare + i))
		{
			return (-1);
		}
	}
	return(2);
}


char *_getenv(const char *name)
{
	int i = 0;
	int is_env = 0;


	for (i = 0; *(__environ + i) != NULL; i++)
	{
		is_env = compare_env_key(name,*(__environ +i));
		if (is_env == 2)
		{
			return(*(__environ + i));
			break;
		}
		
	}
	return(NULL);
}


int main(int ac, char **av, char **env)
{
	const char *name = "PATH";
	char *s = NULL;
	
	printf("Environ via global variable : \n\n");
	print_environ();
	printf("\nEnviron via env in main :\n\n");
	print_array(env);
	printf("\nNow let's try getenv\n\n");
	s = _getenv(name);
	printf("%s\n",s);


	
	
	return (0);
}