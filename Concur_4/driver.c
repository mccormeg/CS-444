/*******************************************************************
 ** Megan McCormick
 ** Concurrency 4 homework
** The Barber Shop problem
** 6/3/18
 ********************************************************************/

/********************************************************************
 ** Include section
 *********************************************************************/

#include "./concurr4.h"
/********************************************************************
 ** Definitions/Global Variables
 *********************************************************************/
//Array of Philosopher names
char* names[10] = {"Abby", "Brian", "Chris" ,"Deric","Erica","Fraiser","Gabby","Hannah","Issac","Jackie"};

int main(){
    init_genrand(time(NULL));
	pthread_t custs[10];
	pthread_t barb;
    int i =0;
	int j;
	//Setup Struct
	struct cust *csts = malloc(sizeof(struct cust)*10);
	for(i = 0; i < 10; i ++){
		strcpy(csts[i].name,names[i]);
	}
	//initiliting locks
	pthread_mutex_init(&display, NULL);
	pthread_mutex_init(&bar, NULL);
	pthread_mutex_init(&cust, NULL);
	pthread_mutex_init(&hair, NULL);
	pthread_cond_init(&barber_a, NULL);
	pthread_cond_init(&cust_a, NULL);
	pthread_cond_init(&hair_a, NULL);
	init_chairs();
	//Creating Mutexes
    printf("Creating thread\n");
	pthread_create(&barb,NULL,barber,NULL);	
    while(1){
		//pthread_mutex_lock(&display);
		//printf("i is: %i\n",i);
		//pthread_mutex_unlock(&display);
		i = numgen(0,9);
		sleep(1);
		if (pthread_create(&custs[i],NULL,customer,&csts[i]) != 0){
			printf("Creation of pthread failed\n");
		}
		pthread_detach(custs[i]);	
		sleep(2);
	}
	pthread_join(barb, NULL);
	/*for (j = 0; j < 5; j++) {
		pthread_join(custs[j],NULL);
	}*/


   return 0;
}
