#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct graph{
	int n;  /* number of vertices */
	int m;  /* number of edges */
	struct successors{
		int d;  /* degree of one vertice */
		int len;  /* number of slots for one vertice */
		int list[1];  /* actual list of successors for one vertice */
	} *alist[1];
} *Graph;

/* create a new graph with n vertices and no edges */
Graph graph_create(int n);

/* free all space used by a graph */
void graph_destroy(Graph g);

/* add an edge to an existing graph */
void graph_add_edge(Graph g, int u, int v);

/* return the number of vertices in the graph */
int graph_vertex_count(Graph g);

/* return the number of edges in the graph */
int graph_edge_count(Graph g);

/* return degree of a vertex */
int graph_degree(Graph g, int s);

/* display a graph */
void graph_display(Graph g);

#endif
