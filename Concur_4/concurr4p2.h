/*******************************************************************
** Megan McCormick
** Concurrency 4 homework
** The Ciggarette problem
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
//Resources Mutex
pthread_mutex_t resources[3];
//Agent Mutex
pthread_mutex_t agent;
//Agent COndition
pthread_cond_t agent_a;
//Tobacco Condition
pthread_cond_t resources_a[3];
//Printing mutex
pthread_mutex_t display;
/********************************************************************
** Function Prototypes
********************************************************************/
void init_resources();
void *smoker(void * para);
void make_cig(int);
void sig_a(int);
void *agents();