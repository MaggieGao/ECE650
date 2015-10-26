#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include "search.h"

/* 
struct search_info{
	Graph g;
	int * flag;
	int * dist;
	int * parent; 
	Queue q;
}; */

/* create an array of n ints */
int * array_create(int n){   
	int * arr;
	int i;
	
	arr = malloc(n * sizeof(int));
	//assert(arr);
	
	for(i = 0; i < n; i++){
		arr[i] = SEARCH_INFO_NULL;
	}
	
	return arr;
}

/* create search_info sturcture with n elements */
struct search_info * search_info_create(Graph g){
	struct search_info *s;
	int n;
	
	s = malloc(sizeof(*s));
	//assert(s);
	
	n = graph_vertex_count(g);
	
	s->g = g;
	s->flag = array_create(n);
	s->dist = array_create(n);
	s->parent = array_create(n);
	s->q = queue_create(n);
	
	return s;
}

/* free all space used by a search_info structure */
void search_info_destroy(struct search_info * s){
	queue_destroy(s->q);
	free(s->parent);
	free(s->dist);
	free(s->flag);
	free(s);
}

/* BFS shortest path finding algorithm */
void BFS(struct search_info * s, int start){
	int i, j;
	int n;
	int u, v;
	
	n = graph_vertex_count(s->g);
	 
	for(i = 0; i < n; i++){
		if(i != start){
			s->flag[i] = 0;  /* 0 denotes the node color is white */
			s->dist[i] = SEARCH_INFO_NULL;
			s->parent[i] = SEARCH_INFO_NULL;
		}
	}
	
	s->flag[start] = 1;
	s->dist[start] = 0;
	s->parent[start] = SEARCH_INFO_NULL;
	
	enqueue(s->q, start);  /* enqueue */
	
	while(s->q->top - s->q->bottom > 0){
		u = dequeue(s->q);  /* dequeue */
		
		for(j = 0; j < s->g->alist[u]->d; j++){ /* for each node adjancent to u */
			v= s->g->alist[u]->list[j]; 
			
			if(s->flag[v] == 0){  /* if node color is white */ 
				s->flag[v] =1;  /* node color change to grey */
				s->dist[v] = s->dist[u] + 1;
				s->parent[v] = u;
				
				enqueue(s->q, v);  /* enqueue */
			}
		}
		s->flag[u] = 2;  /* node color change to black */	
	}
}
