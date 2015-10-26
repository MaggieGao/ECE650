#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>

#include "queue.h"
#include "search.h"

/* typedef struct queue{
	int * qlist;
	int bottom;
	int top;
} * Queue; */ 

/* create an empty queue with n elements */
Queue queue_create(int n){
	Queue q;
	q = malloc(sizeof(*q));
	//assert(q);
	
	q->qlist = array_create(n);
	q->bottom = 0;
	q->top = 0;
	
	return q;
}

/* free all space used by a queue */
void queue_destroy(Queue q){
	free(q->qlist);
	free(q);
}

/* push an element into queue from the back of a queue */
void enqueue(Queue q, int x){
	q->qlist[q->top] = x;
	q->top++;
}

/* pop an element from queue from the head of a queue */
int dequeue(Queue q){
	int data = q->qlist[q->bottom];
	q->qlist[q->bottom] = SEARCH_INFO_NULL; 
	q->bottom ++;
	
	return data;
}

/* display queue */
void queue_display(Queue q, int n){
	int i;
	//int n = sizeof(q->qlist) / sizeof(int);
	printf("n: %d \n", n);
	
	printf("Print queue: ");
	for(i = 0; i < n; i++){
		printf("%d, ", q->qlist[i]);
	}
	printf("\n");
}

