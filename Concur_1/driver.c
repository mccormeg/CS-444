/*******************************************************************
** Megan McCormick
** Concurrency 1 homework
** Producer Consumer Problem
** 4/15/2018
********************************************************************/

/********************************************************************
** Include section
*********************************************************************/

#include "./concurr1.h"

int main(){
	init_genrand(1000000);
	pthread_t consumer, producer;
	
	buff_init();
	pthread_mutex_init(&lock, NULL);
	
	pthread_create(&producer,NULL,produce,NULL);
   while(1) {
      pthread_create(&consumer, NULL,consume, NULL);
      pthread_join(consumer, NULL);
   }
	
	return 0;
}