/*******************************************************************
** Megan McCormick
** Concurrency 2 homework
** The Dining Philosophers Problem
** 4/29/18
********************************************************************/

/********************************************************************
** Include section
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "./mt19937ar.h"

/********************************************************************
** Definitions/Global Variables
*********************************************************************/

//forks Mutex
pthread_mutex_t forks[5];

//Printing mutex
pthread_mutex_t display;

/********************************************************************
** Struct Definitions/Global
********************************************************************/
struct philosos{
	char name[256];
	int place;
};


/********************************************************************
** Function Prototypes
********************************************************************/
//Thinking
void thinking(struct philosos);
//Get_forks
void get_forks(struct philosos);
//Generate Random Number
int numgen(int, int);
//Philosopher
void *philo(void *);
//Initialize forks
void init_forks();
//Eat
void eat(struct philosos);
//Put forks back
void put_forks(struct philosos);

