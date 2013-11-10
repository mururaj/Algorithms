#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	pid = fork();
	
	if (pid == 0)
	{
		execl("/usr/bin/ls","/home/scf-19/mraju",NULL);
		printf("Note that this code will be overwritten\n");
	} else
	{
		printf("I forked a child to do ls\n");
	}
	
	return 1;
}
