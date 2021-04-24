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
 //char* resource[3] = {"Tobacco","Paper","Match"};
int main(){
	pthread_t res [3];
	pthread_t ag;
	pthread_mutex_init(&display, NULL);
	init_resources();
	init_genrand(1000000);
	
	pthread_create(&ag,NULL,agents,NULL);
	int i;
	int j;
	for(i = 0; i < 3; i++){
		sleep(1);
		if (pthread_create(&res[i],NULL,smoker,&i) != 0){
			printf("Creation of pthread failed\n");
		}
	}
	for (j = 0; j < 3; j++) {
		pthread_join(res[j],NULL);
	}
	
	return 0;
}
