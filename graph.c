#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>

#include "graph.h"

/* create a new graph with n vertices and no edges */
Graph graph_create(int n){
	Graph g;
	int i;
	
	g = malloc(sizeof(struct graph) + (n - 1) * sizeof(struct successors *));
	//assert(g);
	
	g->n = n;
	g->m = 0;
	
	for(i = 0; i < n; i++){
		g->alist[i] = malloc(sizeof(struct successors));
		//assert(g->alist[i]);
		
		g->alist[i]->d = 0;  /* no edges */
		g->alist[i]->len = 1;
	}
	
	return g;
}

/* free all space used by a graph */
void graph_destroy(Graph g){
	int i;
	
	for(i = 0; i < g->n; i++){
		free(g->alist[i]);
	}
	
	free(g);
}

/* add edge to an existing graph */
void graph_add_edge(Graph g, int u, int v){
	//assert(u >= 0);
	//assert(u < g->n);
	//assert(v >= 0);
	//assert(v < g->n);
	
	/* resize g->alist[u] to twice as big as its original */
	while(g->alist[u]->d >= g->alist[u]->len){
		g->alist[u]->len *= 2;  
		
		g->alist[u] = realloc(g->alist[u], sizeof(struct successors) 
		              + (g->alist[u]->len - 1) * sizeof(int));
		
	}
	
	g->alist[u]->list[g->alist[u]->d] = v;
	g->alist[u]->d ++;
	
	/* add edge for undirected graph */
	while(g->alist[v]->d >= g->alist[v]->len){
		g->alist[v]->len *= 2;  
		
		g->alist[v] = realloc(g->alist[v], sizeof(struct successors) 
		              + (g->alist[v]->len - 1) * sizeof(int));
		
	}
	
	g->alist[v]->list[g->alist[v]->d] = u;
	g->alist[v]->d ++;
	
	/* add one to the number of edge in the graph */
	g->m ++;
}

/* return the number of vertices in the graph */
int graph_vertex_count(Graph g){
	return g->n;
}

/* return the number of edges in the graph */
int graph_edge_count(Graph g){
	return g->m;
}

/* return degree of a vertex */
int graph_degree(Graph g, int s){
	//assert(s >= 0);
	//assert(s < g->n);
	
	return g->alist[s]->d;
}

/* display a graph */
void graph_display(Graph g){
	int i;
	int j;
	
	for(i = 0; i < g->n; i++){
		for(j = 0; j < g->alist[i]->d; j++){
			printf("<%d, %d> \n", i, g->alist[i]->list[j]);
		}
		
	}
}

