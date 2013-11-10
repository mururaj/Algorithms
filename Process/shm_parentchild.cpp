#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>


int main()
{
	int shmid;
	char *shmPtr;
	int n;

	if (fork() == 0)
	{
		sleep(5);

		shmid = shmget(2041,32,0);

		if (shmid == -1)
		{
			perror("shmget error\n");
			return -1;
		}

		shmPtr = (char *) shmat(shmid, 0, 0);
		if (shmPtr == (char *) -1)
		{
			perror("shmat error\n");
			return -1;
		}

		printf("Child is reading the alphabets\n");
		for (n=0;n<26;n++)
		{
			putchar(shmPtr[n]);
			putchar('\n');
		}
	}
	else
	{
		shmid = shmget(2041,32,0666 | IPC_CREAT);

		if (shmid == -1)
		{
			perror("shmget error\n");
			return -1;
		}

		shmPtr = (char *) shmat(shmid, 0, 0);
		if (shmPtr == (char *) -1)
		{
			perror("shmat error\n");
			return -1;
		}

		for (n=0;n<26;n++)
		{
			shmPtr[n] = 'a'+ n;
		}
		printf("Parent has written the alphabets\n");

		wait(NULL);
		shmdt(shmPtr);

		if (shmctl(shmid,IPC_RMID,NULL) == -1) 
		{
			perror("shmctl error\n");
			return -1;
		}
	}

	return 0;
}


