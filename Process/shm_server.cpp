#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>


#define SHMSZ 30

int main()
{
	char c;
	int shmid;
	key_t key;
	char *shm, *s;

	// name shared memory segment
	key = 9999;

	// Create a new segment
	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
	{
		perror("Shmget failed");
		return -1;
	}

	// Attach memory to the segment
	shm = (char *) shmat(shmid,NULL,0);
	/*
	if ((shm = shmat(shmid, NULL, 0)) == "-1")
	{
		perror("shmat failed");
		return -1;
	}
	*/

	
	s = shm;

	// Write on shared data
	for (c='a';c<='z';c++)
	{
		*s++ = c;
	}
	*s = NULL;

	//Wait till shared data is modified by client
	while (*shm != '*')
	{
		sleep(1);
	}

	printf("client has read the data\n");

	shmctl(shmid, IPC_RMID, NULL);

	return 1;
}


