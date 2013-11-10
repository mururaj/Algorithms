/*
A simple program to check wait call of parent
*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int status;
	unsigned int i =0;
	
	pid = fork();

	if (pid == 0)
	{
		while (i< UINT_MAX/10)
		{
			i++;
			sleep(1);
		}
		printf("Child is done \n");

	} else
	{
		waitpid(pid,&status,NULL);
		if (WIFEXITED(status))
		{
			printf("child terminated normally \n");
		} else
		{
			printf("Child terminated abnormally \n");
			return 0;
		}
	}

	return 1;
}
