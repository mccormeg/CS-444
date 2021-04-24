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
 
/********************************************************************
** Definitions/Global Variables
*********************************************************************/

 int count = 0;
 int reg_count = 0;
 
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

/******************************************************************
** User
** User  process acceses the resource.
******************************************************************/
void *user(){
	int current_count;
	int i;
	
	if(count < 3){
		count ++;
	}
	reg_count ++;
	current_count= reg_count;
	//printf("count out: %i\n",count);
	pthread_mutex_lock(&resource[count]);
		//current_count= reg_count;
		pthread_mutex_lock(&display);
		//printf("count in: %i\n",count);
		pthread_mutex_unlock(&display);
		accesses(current_count);
		if(count == 3){
			count = 0;
			pthread_mutex_lock(&display);
			printf("User %i is consuming...\n",current_count);
			pthread_mutex_unlock(&display);
			sleep(4);
			pthread_mutex_lock(&display);
			printf("User %i is done consuming...\n",current_count);
			pthread_mutex_unlock(&display);
			for( i = 0; i < 3; i++){
				pthread_mutex_unlock(&resource[i+1]);
			}
		}
		else{
			pthread_mutex_lock(&display);
			printf("User %i is consuming...\n",current_count);
			pthread_mutex_unlock(&display);
			sleep(4);
			pthread_mutex_lock(&display);
			printf("User %i is done consuming...\n",current_count);
			pthread_mutex_unlock(&display);
		}		
}

/******************************************************************
** access
** Prints that the thread is accessing the resource
******************************************************************/
void accesses(int a){
	pthread_mutex_lock(&display);
	printf("User %i is accessing the resource...\n",a);
	pthread_mutex_unlock(&display);
}
/******************************************************************
** init resources
** Initilizes three resource locks
******************************************************************/
void init_resources(){
	int i;
	for (i = 0; i < 3; i++) {
		pthread_mutex_init(&resource[i], NULL);
	}
}