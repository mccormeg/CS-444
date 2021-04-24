/*******************************************************************
 ** Megan McCormick
 ** Concurrency 2 homework
 ** The Dining Philosophers Problem
 ** 4/29/18
 ********************************************************************/

/********************************************************************
 ** Include section
 *********************************************************************/

#include "./concurr2.h"



/*********************************************************************
 ** Function Definitions
 **********************************************************************/

/*************************************************************************
 ** numgen
 ** Generates random numbers between a range. Values will generate differently
 ** depending on the system it's run on.
 **************************************************************************/
int numgen(int min, int max){

   int rand_num;
   unsigned int eax;
   unsigned int ebx;
   unsigned int ecx;
   unsigned int edx;

   char vendor[13];

   eax = 0x01;

   __asm__ __volatile__(
	 "cpuid;"
	 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	 : "a"(eax)
	 );

   if(ecx & 0x40000000){
      //use rdrand
      //printf("Using rdrand\n");
      __asm__ __volatile__("rdrand %0": "=r" (rand_num));
      rand_num = abs(rand_num);
      rand_num=(rand_num%(max-min+1))+min;
   }
   else{
      //use mt19937
      //printf("Using mt19937\n");
      rand_num = abs(genrand_int32());
      rand_num=(rand_num%(max-min+1))+min;
   }

   return rand_num;


}
/*******************************************************************
 ** philo
 ** Runs the process for a philosopher
 ** Will wait, get forks, eat, and put forks back
 ********************************************************************/
void *philo(void * para)
{
	struct philosos *name;
	name = (struct philosos *) para;
	while(1){
		//Think
		thinking(*name);
		//Get your forks
		get_forks(*name);
		//eat
		eat(*name);
		//Put forks back
		put_forks(*name);
		sleep(1);
	}
}

/*******************************************************************
 ** Thinking
 ** Creates a time for the philosopher to think 
 ** Exexcutes that thinking time and prints to the screen.
 ********************************************************************/
void thinking(struct philosos name){
	int wait = numgen(1,20);
	pthread_mutex_lock(&display);
	printf(" %s is thinking ...\n", name.name);
	pthread_mutex_unlock(&display);
	sleep(wait);
	pthread_mutex_lock(&display);
	printf(" %s is done thinking.\n", name.name);
	pthread_mutex_unlock(&display);
}
/*******************************************************************
 ** get_forks
 ** Tries to grab left fork and then grab the right fork.
 ** If a fork can't be grabbed it waits
 ********************************************************************/
void get_forks(struct philosos name){
	if(pthread_mutex_lock(&forks[name.place]) == 0){
		pthread_mutex_lock(&display);
		printf(" %s got the right fork, fork %i\n", name.name,name.place);
		pthread_mutex_unlock(&display);
	}
	else{
		pthread_mutex_lock(&display);
		printf(" %s is waiting for the right fork,fork %i\n", name.name,name.place);
		pthread_mutex_unlock(&display);
	}
	if(name.place == 4){
		if(pthread_mutex_lock(&forks[0]) == 0){
			pthread_mutex_lock(&display);
			printf(" %s got the left forkfork %i\n", name.name,0);
			pthread_mutex_unlock(&display);
		}
		else{
			pthread_mutex_lock(&display);
			printf(" %s is waiting for the left fork,fork %i\n", name.name,0);
			pthread_mutex_unlock(&display);
		}
	}
	else{
		if(pthread_mutex_lock(&forks[name.place+1]) == 0){
			pthread_mutex_lock(&display);
			printf(" %s got the left fork,fork %i\n", name.name,name.place+1);
			pthread_mutex_unlock(&display);
		}
		else{
			pthread_mutex_lock(&display);
			printf(" %s is waiting for the left fork,fork %i\n", name.name,name.place+1);
			pthread_mutex_unlock(&display);
		}
	}
	
}
/*******************************************************************
 ** Init_forks
 ** Initiallizes all fork mutexes 
 ********************************************************************/
void init_forks(){
	int i;
	for (i = 0; i < 5; i++) {
		pthread_mutex_init(&forks[i], NULL);
	}
}
/*******************************************************************
 ** Eating
 ** Creates a time for the philosopher to eat 
 ** Exexcutes that eat time and prints to the screen.
 ********************************************************************/
void eat(struct philosos name){
	int wait = numgen(2,9);
	pthread_mutex_lock(&display);
	printf(" %s is eating ...\n", name.name);
	pthread_mutex_unlock(&display);
	sleep(wait);
	pthread_mutex_lock(&display);
	printf(" %s is done eating.\n", name.name);
	pthread_mutex_unlock(&display);
}
/*******************************************************************
 ** put_forks
 ** Puts fork back after eating.
 ********************************************************************/
void put_forks(struct philosos name){
	if(pthread_mutex_unlock(&forks[name.place]) == 0){
		pthread_mutex_lock(&display);
		printf(" %s is putting down the right fork,fork %i\n", name.name,name.place);
		pthread_mutex_unlock(&display);
	}
	else{
		pthread_mutex_lock(&display);
		printf(" %s is waiting to put down the right fork,fork %i\n", name.name,name.place);
		pthread_mutex_unlock(&display);
	}
	if(name.place == 4){
		if(pthread_mutex_unlock(&forks[0]) == 0){
			pthread_mutex_lock(&display);
			printf(" %s is putting down fork,fork %i\n",name.name,0);
			pthread_mutex_unlock(&display);
		}
		else{
			pthread_mutex_lock(&display);
			printf(" %s is waiting to put down the left fork,fork %i\n", name.name,0);
			pthread_mutex_unlock(&display);
		}
	}
	else{
		if(pthread_mutex_unlock(&forks[name.place+1]) == 0){
			pthread_mutex_lock(&display);
			printf(" %s is putting down the left fork,fork %i\n", name.name,name.place+1);
			pthread_mutex_unlock(&display);
		}
		else{
			pthread_mutex_lock(&display);
			printf(" %s is waiting to put down the left fork,fork %i\n", name.name,name.place+1);
			pthread_mutex_unlock(&display);
		}
	}
}



