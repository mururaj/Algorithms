/*
Author: Muruganantham Raju
A simple program to fork a child and print process Ids
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	printf("Forking a new process \n");

	pid = fork();

	if (pid == 0)
	{
		printf("I am child process \n");
		printf("Child: My process Id %d\n", getpid());
		printf("Child: My parent's Id %d\n", getppid());
	} else
	{
		printf("I am the parent process \n");
		printf("Parent: My process Id %d\n", getpid());
		printf("Parent: My child Id %d\n", pid);
	}
	
	return 1;
}
