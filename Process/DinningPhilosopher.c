#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

/*************************************************************************
Solution to Thinking philosophers problem with an SLEEP, EAT, THINK states
Raghu Sarangapani, sarangap@cs.colostate.edu, rsaranga@rams.colostate.edu
Last Updated - Oct 1, 2012
*************************************************************************/

/* enum to fix the various possible states */
enum {THINKING,EATING,SLEEPING,SLEEPY,HUNGRY} state[5];

int N=5;
sem_t sleepsem;        /* Semaphore per philosopher to wait for sleeping */
sem_t pick[5];         /* Semaphore per philosopher to wait for eating */
pthread_mutex_t lock;  /* Mutex to lock take_forks function */
int duration=300;      /* Program run duration */

/* Brief function to take a bed if available, block on it if unavailable*/
void take_bed(int i) {
//	sleep(1);
        int value;
	state[i]=SLEEPY;
//        sem_getvalue(&sleepsem,&value);
//        printf("Thread[%d]: Sleepsm value before wait %d\n",i,value);
	sem_wait(&sleepsem);
        sem_getvalue(&sleepsem,&value);
        printf("Thread[%d]: Sleepsm value after wait %d\n",i,value);
	if(state[i] == SLEEPY){ 
		state[i]=SLEEPING; 
	}
}

/* Brief function to release bed by changing state */
void release_bed(int i) {
	state[i]=HUNGRY;
	sem_post(&sleepsem);
}

/* Brief function to test the availability of forks by checking if the neighbors are eating */
void test_forks(int i){
	if((state[(i+1) % 5] != EATING) && (state[(i+4) % 5] != EATING) && (state[i] == HUNGRY)){
		state[i]=EATING;
		sem_post(&pick[i]);
	}
}

/* Brief function to take forks if available, block on it if unavailable*/
void take_forks(int i) {
	pthread_mutex_lock(&lock);
	state[i]=HUNGRY;
	test_forks(i);
	pthread_mutex_unlock(&lock);
	if(state[i] != EATING){
		sem_wait(&pick[i]);
		take_forks(i);
	}
}

/* Brief function to release forks by changing the state */
void release_forks(int i) {
	state[i]=THINKING;
	test_forks((i+1) % 5);
	test_forks((i+4) % 5);
}

/* Brief function to think for random number of seconds*/
void thinking(int i) {
	if(state[i] == THINKING){
		sleep(rand() % 5 + 1);
	}
}

/* Brief function to eat for random number of seconds */
void eating(int i) {
	if(state[i] == EATING){
		sleep(rand() % 5 + 1);
	}
}

/* Brief function to sleep for random number of seconds*/
void sleeping(int i) {
	if(state[i] == SLEEPING){
		sleep(rand() % 5 + 1);
	}
}

/* Brief function where the threads begin execution */
void *philosopher(void *n) {       
	int i=*(int*)n;
        while(1) {
		take_bed(i);
		sleeping(i);
		release_bed(i);
             //   take_forks(i);
		//eating(i);
                //release_forks(i);
		thinking(i);
        }
}

/* MAIN */
int main(int argc, char *argv[]){
	if(argc > 1){
		duration=atoi(argv[1]);
		if(duration <= 0){
			printf("Usage: %s <Number of seconds>\n",argv[0]);
			exit(1);
		}
	}

	int i, var[N];
	pthread_t tid[N];
	time_t start=time(NULL);
	/* Create a thread for each philosopher, initialize the state to THINKING and initialize two semaphores for each */
	for(i=0;i<N;i++){
		var[i]=i;
		pthread_create(&tid[i], NULL, philosopher, &var[i]);
		state[i]=THINKING;
		sem_init(&pick[i],0,0);
		sem_init(&sleepsem,0,1);
	}

	/* Poll the state variable and print status of every thread for duration seconds */
	while(1){
		if((time(NULL)-start)>duration){
			printf("Elapsed %d seconds, Exiting...\n",duration);
			exit(0);
		}
		for(i=0;i<N;i++){
			if(state[i] == THINKING){
				printf("Philosopher %d: thinking\n",i);
			}
			else if(state[i] == EATING){
				printf("Philosopher %d: eating\n",i);
			}
			else if(state[i] == SLEEPING){
				printf("Philosopher %d: sleeping\n",i);
			}
			else if(state[i] == SLEEPY){
				printf("Philosopher %d: waiting to sleep\n",i);
			}
			else if(state[i] == HUNGRY){
				printf("Philosopher %d: waiting to eat\n",i);
			}
		}
		printf("\n");
		sleep(1);
	}
}
