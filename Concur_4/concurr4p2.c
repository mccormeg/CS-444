/*******************************************************************
** Megan McCormick
** Concurrency 4 homework
** The Ciggarette problem
** 6/3/18
********************************************************************/
/********************************************************************
 ** Include section
 *********************************************************************/

#include "./concurr4p2.h"

/********************************************************************
** Definitions/Global Variables
*********************************************************************/
 char* resource[3] = {"Tobacco","Paper","Match"};

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
 ** Init_resouces
 ** Initiallizes all chairs mutexes 
 ********************************************************************/
void init_resources(){
	int i;
		pthread_mutex_init(&agent, NULL);
		pthread_cond_init(&agent_a, NULL);
	for (i = 0; i < 3; i++) {
		pthread_mutex_init(&resources[i], NULL);
		pthread_cond_init(&resources_a[i], NULL);
	}
}
/*******************************************************************
 ** smoker
 ** Runs the process for a customer
 ** Will wait for the barber or leave if there are no seats
 ********************************************************************/
void *smoker(void * para){
		int *res;
		res = (int *) para;
		int i = (*res) - 1;
	while(1){
		pthread_mutex_lock(&display);
		printf("Smoker with %s is waiting...\n", resource[i]);
		pthread_mutex_unlock(&display);
		if(i == 0){
			
			pthread_mutex_lock(&resources[1]);
			pthread_cond_wait(&resources_a[1], &resources[1]);
			pthread_mutex_unlock(&resources[1]);
			//pthread_mutex_lock(&resources[2]);
			//pthread_cond_wait(&resources_a[2], &resources[2]);
			//pthread_mutex_unlock(&resources[2]);
		}
		else if(i == 1){
			pthread_mutex_lock(&resources[2]);
			pthread_cond_wait(&resources_a[2], &resources[2]);
			pthread_mutex_unlock(&resources[2]);
			//pthread_mutex_lock(&resources[0]);
			//pthread_cond_wait(&resources_a[0], &resources[0]);
			//pthread_mutex_unlock(&resources[0]);
			
		}
		else {
			pthread_mutex_lock(&resources[0]);
			pthread_cond_wait(&resources_a[0], &resources[0]);
			pthread_mutex_unlock(&resources[0]);
			//pthread_mutex_lock(&resources[1]);
			//pthread_cond_wait(&resources_a[1], &resources[1]);
			//pthread_mutex_unlock(&resources[1]);
		}
		make_cig(i);
		sig_a(i);
		sleep(1);
	}
}
/*******************************************************************
 ** agents
 ** Runs the process for a Agent
 ** Will hand out resources
 ********************************************************************/
void *agents(){
		while(1){
		pthread_mutex_lock(&display);
		printf("Agent is waiting.\n");
		pthread_mutex_unlock(&display);
		int a = numgen(0,2);
		int b = numgen(0,2);
		while(b == a){
			b = numgen(0,2);
		}
		pthread_mutex_lock(&display);
		printf("Agent is producing resources %d and %d.\n",a,b);
		printf("Agent is producing resources %s and %s.\n",resource[a],resource[b]);
		pthread_mutex_unlock(&display);
		if((a == 0 && b == 1) || (a == 1 && b==0)){
			pthread_cond_signal(&resources_a[0]);
			//pthread_cond_signal(&resources_a[1]);
		}
		else if ((a == 0 && b == 2) || (a == 2 && b==0)){
			pthread_cond_signal(&resources_a[2]);
			//pthread_cond_signal(&resources_a[0]);
		}
		else{
			pthread_cond_signal(&resources_a[1]);
			//pthread_cond_signal(&resources_a[2]);
		}
		pthread_mutex_lock(&agent);
		pthread_cond_wait(&agent_a, &agent);
		pthread_mutex_unlock(&agent);
		sleep(1);
	}
}
/*******************************************************************
 ** make_cig
 ** Creates a cig
 ********************************************************************/
void make_cig(int a){
	pthread_mutex_lock(&display);
	printf("Smoker with %s is making a cigarette\n", resource[a]);
	pthread_mutex_unlock(&display);
	sleep(1);
}
/*******************************************************************
 ** Signal Agent
 ** signals Agent
 ********************************************************************/
void sig_a(int a){
	pthread_mutex_lock(&display);
	printf("Smoker with %s is telling the agent he's done.\n", resource[a]);
	pthread_mutex_unlock(&display);
	sleep(1);
	pthread_cond_signal(&agent_a);
}
