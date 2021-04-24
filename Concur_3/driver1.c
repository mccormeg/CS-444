/*******************************************************************
 ** Megan McCormick
 ** Concurrency 2 homework
 ** Problem 1, mutual exclusion with 3 processes
 ** 5/14/18
 ********************************************************************/

/********************************************************************
 ** Include section
 *********************************************************************/
 #include "./prob1.h"
 
 
 int main(){
	 int i;
	 int j;
	 pthread_t users[12];
	 init_genrand(time(NULL));
	 //Initilize display
	 pthread_mutex_init(&display, NULL);
	 //Initilize resource
	 void init_resources();
	 //INitilize access
	 pthread_mutex_init(&can_access, NULL);
	 
	for(i = 0; i < 6; i++){
		pthread_mutex_lock(&display);
		//printf("i is: %i\n",i);
		pthread_mutex_unlock(&display);
		sleep(1);
		if (pthread_create(&users[i], NULL, user, NULL) != 0){
			printf("Creation of pthread failed\n");
		}	
	}
	for (j = 0; j < 6; j++) {
		pthread_join(users[j],NULL);
	}
 }