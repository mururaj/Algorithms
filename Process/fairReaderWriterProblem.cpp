#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXTHREADS 50

// initialize locks and CVs
pthread_mutex_t blogLock;
pthread_cond_t writersLeftCV;
pthread_cond_t okToWriteCV;

// initialize all global variables
int blogData = 0;
int numWaitingReaders =0 ,numWaitingWriters =0;
int numActiveReaders =0;
char writeInProgress = 'N';

void acquireReaderLock()
{
	pthread_mutex_lock(&blogLock);

	while(writeInProgress == 'Y')
	{
		++numWaitingReaders;
		pthread_cond_wait(&writersLeftCV,&blogLock);
		--numWaitingReaders;
	}

	++numActiveReaders;

	pthread_mutex_unlock(&blogLock);
}

void releaseReaderLock()
{
	pthread_mutex_lock(&blogLock);
		--numActiveReaders;

		if (numActiveReaders == 0)
		{
			pthread_cond_broadcast(&okToWriteCV);
		}

	pthread_mutex_unlock(&blogLock);
}

void acquireWriterLock()
{
	pthread_mutex_lock(&blogLock);
	
		while( numActiveReaders > 0 ||
			     writeInProgress == 'Y' )
	{
			++numWaitingWriters;
			pthread_cond_wait(&okToWriteCV,&blogLock);
			--numWaitingWriters;
	}
	
		writeInProgress = 'Y';
}

void releaseWriterLock()
{
		writeInProgress = 'N';
		
		if (numWaitingReaders > 0)
		{
			pthread_cond_broadcast(&writersLeftCV);
		} else
		{
			pthread_cond_signal(&okToWriteCV);
		}	
		
	pthread_mutex_unlock(&blogLock);
}


void *readBlog(void *threadId)
{
	//while(1)
	{
	acquireReaderLock();
	printf("Reader %d: Content %d\n",(int *)threadId,
								blogData);
	releaseReaderLock();
	}
	pthread_exit(NULL);
}

void *writeBlog(void *threadId)
{
	//while(1) 
	{
	acquireWriterLock();
	blogData = rand() % 500 + 1;
	printf("Writer %d: Wrote %d\n",(int *)threadId,
							blogData);
	releaseWriterLock();
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_mutex_init(&blogLock,NULL);
	pthread_cond_init(&okToWriteCV,NULL);
	pthread_cond_init(&writersLeftCV,NULL);

	int numThreads;
	int randNum;

	printf("Enter number of threads\n");
	scanf("%d",&numThreads);


	if (numThreads > MAXTHREADS)
	{
		printf("Error: Total number of threads exceeds max limit \n");
		exit(-1);
	}

	const int *size = &numThreads;
	

	pthread_t threadId[*size];

	for (int i=0;i<numThreads;i++)
	{
		randNum = rand() % 10 + 1;

		if (randNum <= 7)
		{
			pthread_create(&threadId[i],NULL,readBlog,(void *)i);
		} else
		{
			pthread_create(&threadId[i],NULL,writeBlog,(void *)i);
		}
		
	}

	pthread_exit(NULL);

	return 0;
}
