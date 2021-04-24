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
/********************************************************************
 ** Definitions/Global Variables
 *********************************************************************/
//Array of Philosopher names
char* philosophers[5] = {"Yajnavalkya", "Plato", "Dork Sahagian" ,"Francis Bacon","Simplicius of Cilicia"};

int main(){
    init_genrand(time(NULL));
	pthread_t philosopher[5];
    int i =0;
	int j;
	//Setup Struct
	struct philosos *ps = malloc(sizeof(struct philosos)*5);
	for(i = 0; i < 5; i ++){
		strcpy(ps[i].name,philosophers[i]);
		ps[i].place = i;
	}
	//initiliting locks
	pthread_mutex_init(&display, NULL);
	init_forks();
	//Creating Mutexes
    printf("Creating thread\n");	
    for(i = 0; i < 5; i++){
		pthread_mutex_lock(&display);
		printf("i is: %i\n",i);
		pthread_mutex_unlock(&display);
		sleep(1);
		if (pthread_create(&philosopher[i],NULL,philo,&ps[i]) != 0){
			printf("Creation of pthread failed\n");
		}	
	}
	for (j = 0; j < 5; j++) {
		pthread_join(philosopher[j],NULL);
	}


   return 0;
}
