/*******************************************************************
 ** Megan McCormick
 ** Concurrency 2 homework
 ** Problem 2, mutual exclusion with 3 processes
 ** 5/14/18
 ********************************************************************/

/********************************************************************
 ** Include section
 *********************************************************************/
 #include "./prob2.h"
 
 
 int main(){
	 int i,j,k,l,m,n,o;
	 pthread_t in[11];
	 pthread_t del[11];
	 pthread_t ser[11];
	 init_genrand(time(NULL));
	 //Initilize display
	 pthread_mutex_init(&display, NULL);
	 //Initilize search lock
	 pthread_mutex_init(&search_lock, NULL);
	  //Initilize add lock
	 pthread_mutex_init(&add_lock, NULL);
	  //Initilize deletion lock
	 pthread_mutex_init(&del_lock, NULL);
	 
	
	for(i = 0; i < 10; i++){
		sleep(1);
		if (pthread_create(&in[i], NULL, insert, NULL) != 0){
			printf("Creation of pthread failed\n");
		}	
		if (pthread_create(&ser[i], NULL, search, NULL) != 0){
			printf("Creation of pthread failed\n");
		}	
		if (pthread_create(&del[i], NULL, deleted, NULL) != 0){
			printf("Creation of pthread failed\n");
		}	
	}
	for (k = 0; k< 10; k++) {
		pthread_join(in[k],NULL);
		pthread_join(ser[k],NULL);
		pthread_join(del[k],NULL);
	}
 }