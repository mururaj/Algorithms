#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHMSZ 30


int main()
{
	int shmid;
	key_t key;
	char *shm, *s;

	key = 9999;

	if ((shmid = shmget(key, SHMSZ, 0666)) < 0)
	{
		perror("Shmget failed");
		return -1;
	}

	if ((shm = (char *) shmat(shmid, NULL, 0)) == (char *) -1)
	{
		perror("Shmat failed");
		return -1;
	}

	for (s = shm; *s !=NULL ; s++)
	{
		putchar(*s);
		putchar('\n');
	}

	*shm = '*';

	return 1;

}


