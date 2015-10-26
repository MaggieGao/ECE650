#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queue{
	int * qlist;
	int bottom;
	int top;
} *Queue;

/* create an empty queue with n elements */
Queue queue_create(int n);

/* free all space used by a queue */
void queue_destroy(Queue q);

/* push an element into queue from the back of a queue */
void enqueue(Queue q, int x);

/* pop an element from queue from the head of a queue */
int dequeue(Queue q);

/* display queue */
void queue_display(Queue q, int n);

#endif
