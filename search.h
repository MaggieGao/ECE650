#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "queue.h"
#include "graph.h"

#define SEARCH_INFO_NULL (-1)  /* for empty slot */

struct search_info{
	Graph g;
	int * flag;
	int * dist;
	int * parent; 
	Queue q;
};

/* create an array of n ints */
int * array_create(int n);

/* create search_info sturcture with n elements */
struct search_info * search_info_create(Graph g);

/* free all space used by a search_info structure */
void search_info_destroy(struct search_info * s);

/* BFS shortest path finding algorithm */
void BFS(struct search_info * s, int start);

#endif
