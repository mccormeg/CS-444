/*******************************************************************
** Megan McCormick
** Concurrency 1 homework
** Producer Consumer Problem
** 4/15/2018
********************************************************************/

/********************************************************************
** Include section
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "./mt19937ar.h"

/********************************************************************
** Definitions/Global Variables
*********************************************************************/
//Buffer size definition
#define BUFFER_SIZE 32

//Struct definition
struct item{
	int value;
	int wait_time;
};

//Lock Pthread
pthread_mutex_t lock;

/********************************************************************
** Function Prototypes
********************************************************************/
//Add item
void item_add(struct item);
//Remove item
struct item delete_item();
//Generate Random Number
int numgen(int, int);
//Producer
void *produce();
//Consumer
void *consume();
//Initialize Buffer
void buff_init();

