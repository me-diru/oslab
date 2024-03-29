#include <pthread.h>

#include <semaphore.h>

#include <stdio.h>

#define N 5

#define THINKING 2

#define HUNGRY 1

#define EATING 0

#define LEFT (phnum + 4) % N

#define RIGHT (phnum + 1) % N

int state[N];

int phil[N] = { 0, 1, 2, 3, 4};

sem_tmutex;

sem_tS[N];

void test(int phnum)
{

	if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
	 {

  		  // state that eating 
		state[phnum] =EATING;
		 sleep(2);
	
		printf("Philosopher %d takes fork %dand%d\n",phnum + 1, LEFT + 1, phnum +1); 
		printf("Philosopher %d is Eating\n", phnum+1);
		sem_post(&sem_tS[phnum]); // sem_post(&S[phnum]) has no effect during takefork used to wake up hungry philosophers during putfork

	}

}



// take up chopsticks

void take_fork(int phnum)

{

	sem_wait(&sem_tmutex);

	state[phnum] = HUNGRY; // state that hungry

	printf("Philosopher %d is Hungry\n", phnum +1);

	test(phnum); // eat if neighbours are not eating

	sem_post(&sem_tmutex);

	sem_wait(&sem_tS[phnum]); // if unable to eat wait to be signalled sleep(1);
}

void put_fork(int phnum)

{

	sem_wait(&sem_tmutex);

	state[phnum] = THINKING;

	printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1); 
	printf("Philosopher %d is thinking\n", phnum + 1); 
	test(LEFT);
	test(RIGHT);

	sem_post(&sem_tmutex);

}

void* philospher(void* num)

{

	while (1)
	 {

		int* i = num;

		sleep(1);

		take_fork(*i);

		sleep(0);

		put_fork(*i); 
	}

}

int main()

{

	int i;

	pthread_t thread_id[N];

	sem_init(&sem_tmutex, 0, 1);

	for (i = 0; i < N; i++)
	
		sem_init(&sem_tS[i], 0, 0);

	for (i = 0; i < N; i++) 
	{

		pthread_create(&thread_id[i], NULL,philospher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);

	}
	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);
	return 0;

}
