#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(void)
{
	__pid_t parent_pid;
	__pid_t child_pid;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	int i = 0;
	int status;

	
	for (i = 0; i <=5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error\n");
		}
		if (child_pid == 0)
		{
			parent_pid = getppid();
			printf("Im the child %d. My parent is %u and lauching a mess\n", i, parent_pid);
			 if (execve(argv[0], argv, NULL) == -1)
			{
			perror("Error:");
			}
		}
		else
		{
			wait(&status);
			printf("Now daddy comes home for the %d time\n", i);
		}
	}

	return (0);

}