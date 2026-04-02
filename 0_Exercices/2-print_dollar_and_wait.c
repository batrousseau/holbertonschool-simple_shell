#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{

char *lineptr = NULL;
size_t n = 0L;
int getline_status = 0;


printf("$ ");
getline_status = getline(&lineptr, &n, stdin);

if (getline_status == -1)
{
	perror("Error with getline initialization\n");
	return (-1);
}
printf("%s", lineptr);
free(lineptr);

return(0);
}