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
 ** customer
 ** Runs the process for a customer
 ** Will wait for the barber or leave if there are no seats
 ********************************************************************/
void *customer(void * para)
{
	struct cust *name;
	name = (struct cust *) para;
	int i;
	for(i = 0; i < 5; i++){
		if(pthread_mutex_trylock(&chairs[i]) == 0){
			pthread_mutex_lock(&display);
			printf("Customer %s: I'll just wait in this chair\n", name->name);
			pthread_mutex_unlock(&display);
			pthread_cond_signal(&cust_a);
			pthread_mutex_lock(&bar);
			pthread_cond_wait(&barber_a, &bar);
			pthread_mutex_unlock(&bar);
			get_hair_cut(*name);
			pthread_cond_signal(&hair_a);
			pthread_mutex_unlock(&chairs[i]);
			break;
		}
	}
	exit_shop(*name);
}
/*******************************************************************
 ** barber
 ** Runs the process for a barber
 ** Takes a snooze if there aren't any customers
 ********************************************************************/
void *barber()
{

	while(1){
		pthread_mutex_lock(&cust);
		pthread_mutex_lock(&display);
		printf("Barber: *yawn* \n");
		pthread_mutex_unlock(&display);
		pthread_cond_wait(&cust_a,&cust);
		pthread_mutex_unlock(&cust);
		pthread_mutex_lock(&display);
		printf("Barber: I'm awake! Who's next?\n");
		pthread_mutex_unlock(&display);
		pthread_cond_signal(&barber_a);
		pthread_mutex_lock(&hair);
		pthread_cond_wait(&hair_a,&hair);
		cut_hair();
		pthread_mutex_unlock(&hair);
	}
}
/*******************************************************************
 ** Init_chairs
 ** Initiallizes all chairs mutexes 
 ********************************************************************/
void init_chairs(){
	int i;
	for (i = 0; i < 5; i++) {
		pthread_mutex_init(&chairs[i], NULL);
	}
}
/*********************************************************************
** Get_hair_cut
** Customer gets their hair cut_hair
**********************************************************************/
void get_hair_cut(struct cust a){
	pthread_mutex_lock(&display);
	printf("Customer %s: Just a trim.\n",a.name);
	pthread_mutex_unlock(&display);
	sleep(numgen(1,5));
}
/**********************************************************************
** exit
** Customer Exits
**********************************************************************/
void exit_shop(struct cust a){
	pthread_mutex_lock(&display);
	printf("Customer %s: Thanks!\n", a.name);
	pthread_mutex_unlock(&display);
	pthread_exit(NULL);
}
/**********************************************************************
** cut_hair
** Barber Cuts a customers hair
**********************************************************************/
void cut_hair(){
	pthread_mutex_lock(&display);
	printf("Barber: All done!\n");
	sleep(1);
	pthread_mutex_unlock(&display);
}



