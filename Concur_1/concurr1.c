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

/********************************************************************
** Definitions/Global Variables
*********************************************************************/
int num_item = 0;

//Static array of items
struct item buff[BUFFER_SIZE];

/*********************************************************************
** Function Definitions
**********************************************************************/

/*********************************************************************
** item_add
** Takes a strcut item and adds itto the buffer
*********************************************************************/
void item_add(struct item new_item){
	//Check that the count wont excede 32
	if (num_item <=31){
		//Add item
		buff[num_item] = new_item;
		//Up count
		num_item ++;
	}
	//Print error if the buffer is full
	else{
		printf("Error: Buffer is full cannot add item\n");
	}
	
	
}
/********************************************************************
** item_delete
** Selects the first item in the buffer, deletes it, rearanges the 
** items in the buffer and returns the item that was deleted. (Pop)
********************************************************************/
struct item delete_item(){
	//Save buffer item at 0
	struct item temp = buff[0];
	int i;
	//Re-adjust buffer
	if(num_item == 1){
		buff[0].value =0;
		buff[0].wait_time =0;
	}
	else{
		for (i = 0; i<num_item-1;i++){
			buff[i] = buff[i+1];
		}
		//Set last value back to default
		buff[num_item].value =0;
		buff[num_item].wait_time =0;
	}
	//Decreate count
	num_item --;
	//Return temp
	return temp;
	
}
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
** produce
** Produces items into the buffer and random intervals of 3-7 
** seconds
********************************************************************/
void *produce()
{
	struct item new_item;
	int produce_sleep;
	while(1){
		//lock the mutex so other threads can't use it
		pthread_mutex_lock(&lock);
		//Create new item
		new_item.value = numgen(1,100);
		new_item.wait_time = numgen(2,9);
		//Add item to buffer
		printf("Producing...\n");
		item_add(new_item);
		//Unlock pthread
		pthread_mutex_unlock(&lock);
		//sleep for some time
		produce_sleep = numgen(3,7);
		sleep(produce_sleep);
	}
}
/*******************************************************************
** consume
** Consumesthe first item of the buffer printing out its value and 
** using it's wait time before consuming the next item
********************************************************************/
void *consume(){
	struct item deleted_item;
	while(1){
		//lock the mutex so other threads can't use it
		pthread_mutex_lock(&lock);
		if(buff[0].value != 0){
			//Grab Item from buffer
			deleted_item = delete_item();
			printf("Consuming item .....\n");
			//Unlock pthread
			pthread_mutex_unlock(&lock);
			//Sleep to consume
			sleep(deleted_item.wait_time);
			//Print value
			printf("Consumed value of %d\n",deleted_item.value);
		}
		//Unlock pthread
		pthread_mutex_unlock(&lock);
	}
}

/*********************************************************************
** buff_init
** initilizes buffer to all 0s
*********************************************************************/
void buff_init(){
	int i;
	for (i = 0; i<BUFFER_SIZE;i++){
		buff[i].value = 0;
		buff[i].wait_time = 0;
	}
	
}




