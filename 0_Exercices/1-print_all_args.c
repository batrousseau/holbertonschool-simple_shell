#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>



int main(int ac, char **av)
{

	int i = 0;

	for (i = 1; av[i] != NULL; i++)
	{

		printf("%s ", av[i]);
	}
	printf("\n");
	return (0);
}