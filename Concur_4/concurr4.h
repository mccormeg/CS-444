/*******************************************************************
** Megan McCormick
** Concurrency 4 homework
** The Barber Shop problem
** 6/3/18
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

//chairs Mutex
pthread_mutex_t chairs[5];
//Barber Busy
pthread_mutex_t bar;
//Cust Busy
pthread_mutex_t cust;
//Printing mutex
pthread_mutex_t display;
//Baber Condition
pthread_cond_t barber_a;
//Cust Condition
pthread_cond_t cust_a;
//Done cutting hair
pthread_mutex_t hair;
//Hair condition
pthread_cond_t hair_a;


/********************************************************************
** Struct Definitions/Global
********************************************************************/
struct cust{
	char name[256];
	int place;
};


/********************************************************************
** Function Prototypes
********************************************************************/
//Get Hair cut
void get_hair_cut(struct cust);
//Exit shop
void exit_shop(struct cust);
//Generate Random Number
int numgen(int, int);
//Customer
void *customer(void *);
//Barber
void *barber();
//Initialize chairs
void init_chairs();
//Cut hair
void cut_hair();


