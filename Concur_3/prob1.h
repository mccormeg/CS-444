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

//Resource mutex
pthread_mutex_t resource[3];

//Printing mutex
pthread_mutex_t display;

//Can access
pthread_mutex_t can_access;



/********************************************************************
** Function Prototypes
********************************************************************/
//Generate Random Number
int numgen(int, int);
//User thread
void *user();
//Access the shared data
void accesses(int);
//Initilize resources
void init_resources();
