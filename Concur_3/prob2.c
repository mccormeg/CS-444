/*******************************************************************
 ** Megan McCormick
 ** Concurrency 2 homework
 ** Problem 2, mutual exclusion with 3 processes
 ** 5/14/18
 ********************************************************************/

/********************************************************************
 ** Include section
 *********************************************************************/
 #include "./prob2.h"
/********************************************************************
** Definitions/Global Variables
*********************************************************************/
struct node *head = NULL;
 /*********************************************************************
 ** Function Definitions
 **********************************************************************/

 /*********************************************************************************
** Function: newNode
** Description: creates a new node
** Parameters: int x 
** Pre-Conditions: no node
** Post-conditions: new node
*********************************************************************************/
struct node* newnode(int x) {
	//creates a new node and sets all pointers to NULL for the time being
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}
/*********************************************************************************
** Function: append
** Description: puts a new node at the end
** Parameters: struct node *headRef,struct node *tailRef, int num
** Pre-Conditions: Normal list
** Post-conditions: List with new tail
*********************************************************************************/
void append(int num){
	struct node* current = head;
	struct node* newNode;
	newNode = newnode(num);
	//Appends to the front if the first node
	if (current == NULL) {
		head = newNode;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}

}
/*********************************************************************************
** Function: append
** Description: puts a new node at the end
** Parameters: struct node *headRef,struct node *tailRef, int num
** Pre-Conditions: Normal list
** Post-conditions: List with new tail
*********************************************************************************/
void searching(int num){
	struct node* current = head;
	struct node* newNode;
	newNode = newnode(num);
	//Appends to the front if the first node
	if (current == NULL) {
		printf("Could not find %i.\n",num);
	}
	else {
		while (current->next != NULL) {
			if(current->data == num){
				printf("Found %i.\n",num);
				break;
			}
			current = current->next;
		}
		printf("Could not find %i.\n",num);
	}

}
/*********************************************************************************
** Function: removenode
** Description: removes a single node from the list
** Parameters: struct node *headRef, int num
** Pre-Conditions: Linked list
** Post-conditions: Linked list minus 1 node
*********************************************************************************/
void removenode(int num){
	//Takes in the value of the node
	int counter = 0,pos,total;
	struct node* current = head;
	struct node* rest = head;
	//Finds the value
	while (current != NULL) {
		if(current->data == num){
			pos = counter;
			break;
		}
		else{
			current = current->next;
			counter++;
		}
		
	}
	counter = 0;
	while (current != NULL) {	
		current = current->next;
		counter++;
	}	
	total = counter;
	counter = 0;
	current = head;
	//If the position is at the beginning, uses the next node as the head
	if (pos == 0){
		rest= rest->next;
		head = rest;
	}
	//Otherwise find the node before it and reconnect to the node after it.
	else if(pos<total){
		while(counter != pos-1){
			current= current->next;
			rest = rest->next;
			counter++;
		}
		rest = rest->next;
		rest = rest->next;
		current->next = rest;
	}
	else{
		printf("Couldn't delete %i.\n",num);
	}
	
}
 //Search thread
void *search(void *num){
	int wait = numgen(1,5);
	int val = numgen(1,20);
	//pthread_mutex_lock(&search_lock);
	//pthread_mutex_lock(&add_lock);
	pthread_mutex_lock(&display);
	printf("Searching for %i ...\n",val);
	pthread_mutex_unlock(&display);
	sleep(wait);
	searching(val);
	pthread_mutex_lock(&display);
	printf("Done searching for %i.\n",val);
	pthread_mutex_unlock(&display);
	//pthread_mutex_unlock(&add_lock);
	//pthread_mutex_unlock(&search_lock);
}
//Insert thread
void *insert(void *num){
	int wait = numgen(1,5);
	int val = numgen(1,20);
	pthread_mutex_lock(&add_lock);
	pthread_mutex_lock(&del_lock);
	pthread_mutex_lock(&display);
	printf("Inserting %i ...\n",val);
	pthread_mutex_unlock(&display);
	append(val);
	sleep(wait);
	pthread_mutex_lock(&display);
	printf("Done inserting %i.\n",val);
	pthread_mutex_unlock(&display);
	pthread_mutex_unlock(&add_lock);
	pthread_mutex_unlock(&del_lock);
}
//Delete thread
void *deleted(void *num){
	int wait = numgen(1,5);
	int val = numgen(1,20);
	pthread_mutex_lock(&add_lock);
	pthread_mutex_lock(&del_lock);
	pthread_mutex_lock(&display);
	printf("Deleting %i ...\n",val);
	pthread_mutex_unlock(&display);
	removenode(val);
	sleep(wait);
	pthread_mutex_lock(&display);
	printf("Done deleting %i.\n",val);
	pthread_mutex_unlock(&display);
	pthread_mutex_unlock(&del_lock);
	pthread_mutex_unlock(&add_lock);
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