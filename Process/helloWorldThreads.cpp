#include <stdio.h>
#include <pthread.h>

#define MAXTHREADS 5

void *printHW(int threadId)
{
	printf("Thread %d: Hello World\n",threadId);
	pthread_exit(NULL);
}

int main()
{
	
	pthread_t userThreads[MAXTHREADS];
	
	for (int i=0;i<MAXTHREADS;i++)
	{
		pthread_create(&userThreads[i],NULL,printHW,i);
	}
	
	pthread_exit(NULL);
	
	return 0;
}
