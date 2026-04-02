#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int main(void)
{

	__pid_t ppid = 0;
	__pid_t pid = 0;

	pid = getpid();
	ppid = getppid();

	printf("PID is %u and PPID is %u\n",pid, ppid);

	return(0);
}