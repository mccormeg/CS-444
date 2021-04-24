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
pthread_mutex_t search_lock;

//Printing mutex
pthread_mutex_t add_lock;

//Can access
pthread_mutex_t del_lock;

//Printing mutex
pthread_mutex_t display;
/********************************************************************
** Struct Definitions/Global
********************************************************************/
//Node struct for the linked list
struct node{
	int data;
	struct node *next;	
};
/********************************************************************
** Function Prototypes
********************************************************************/
//Search thread
void *search(void *);
//Insert thread
void *insert(void *);
//Delete thread
void *deleted(void *);
//Generate Random Number
int numgen(int, int);
//Remove a node
void removenode(int num);
//Search for a number
void searching(int num);
//Append to the back of the list
void append(int num);
//Create a new node
struct node* newnode(int x);
