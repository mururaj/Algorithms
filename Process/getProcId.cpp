#include <stdio.h>
#include <unistd.h>


int main()
{
	pid_t pid,ppid;
	gid_t gid;

	if ((pid = getpid()) < 0)
	{
		perror("Unable to get proc ID\n");
		return 0;
	} else
	{
		printf("Process is id %d \n",pid);
	}

	if ((ppid = getppid()) < 0)
	{
		perror("Unable to get parent proc ID \n");
		return 0;
	} else
	{
		printf("Parent process id %d \n",ppid);
	}

	if ((gid = getgid()) <0)
	{
		perror("Unable to get group ID \n");
		return 0;
	} else
	{
		printf("Groud id is %d \n",gid);
	}
		 
	return 1;
}
