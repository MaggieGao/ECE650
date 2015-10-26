#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include "graph.h"
#include "queue.h"
#include "search.h"

#define DEFAULT_SIZE (-1)

void shortest_path_show(struct search_info * s, int start, int end);

int main(){
	char mode;  /* mode selection */
	char str[200];  /* store command parameters as a string */
	int num = DEFAULT_SIZE;  /* number of vertices in graph with DEFAULT_SIZE = -1 */
	int source, dest;  /* end points of an edge to add to graph */
	int total_n = 0;  /* for edge point read */
	int n = 0;  /* to record the number of characters read so far, use %n to record */ 
	int start, end;  /* start and end points that request to search shortest path */
	Graph g;
	struct search_info * s;  
	
	int c; /* store data from getchar() */
	int beginning_of_file = 1;  /* mark the beginning of testing file */

	while(1){
		if(beginning_of_file){
			c = getchar();
			mode = c;
			beginning_of_file = 0;
		}
		else{
			while((c = getchar()) != '\n'){
			}
			c = getchar();
			mode = c;
		}
		
		/* if reach end of testing file, quit while loop */	
		if (c == EOF){
			break;
		}
		
		scanf(" %s", str);  // get parameters of a selected mode
		
		switch(mode){
		case 'V':
		case 'v':
			sscanf(str, "%d", &num);
			
			/* test if graph vertex number is not defined or is a negative number */
			if(num < 0){
				printf("Error: Invalid vertex number declaration. \n");
				break;
			}
			
			g = graph_create(num);
			break;			
			
		case 'E':
		case 'e':
			/* test if graph vertex number is not defined or is a negative number */
			if (num < 0){
				printf("Error: Undefined graph vertex number. \n");
				break;
			}
			
			/* read graph edge from str */
			while (2 == sscanf(str + total_n, "%*[^0-9]%d%*[^0-9]%d%n", &source, &dest, &n)){
				/* test if edge definition is out of valid number */
				if(source  < 0 || source >= num || dest < 0 || dest >= num){
					printf("Error: Invalid edge declaratin. Vertex number out of range. \n");
					graph_destroy(g); /* free the memory space used by current graph */
					num = DEFAULT_SIZE; /* reset number of vertices in graph if edge is not correctly defined */
					break;
				}
				
				total_n += n;
				graph_add_edge(g, source, dest);
			}
			
			n = 0;
			total_n = 0;
			break;
		
		case 'S':
		case 's':
			/* read start and end point from quiry statement */
			sscanf(str, "%d", &start);
			scanf("%d", &end);
			
			/* test if graph vertex number is not defined or is a negative number */
			if (num < 0){
				printf("Error: Undefined graph vertex number! \n");
				break;
			}
			
			/* test if graph edge is not defined */
			if (g->m == 0){
				printf("Error: Undefined graph edge. \n");
				graph_destroy(g); /* free the memory space used by current graph */
				num = DEFAULT_SIZE; /* reset number of vertices in graph if edge is not correctly defined */
				break;
			}
		
			/* test if quiry statemnt is a valid */
			if(start  < 0 || start >= num || end < 0 || end >= num){
				printf("Error: Invalid quiry declaration. Vertex number out of range. \n");
				break;
			}
			
			s = search_info_create(g);
			shortest_path_show(s, start, end);
			search_info_destroy(s);
			break;
			
		default:
			printf("Error: Unknown command. \n");
		}
	}  
	
	/* if exist a successfully generated graph, destroy it */
	if (num != DEFAULT_SIZE){
		graph_destroy(g);
	}
	return 0;
}

void shortest_path_show(struct search_info * s, int start, int end){
	int * path_list;  /* record nodes in the shortest path */
	int n;  /* number of vertices in graph  */
	int i;  /* for loop iterator */
	int list_len;  /* length of the list that store nodes in the shortest path */
	int next;
	 
	BFS(s, start);  

	/* if start equals to end point print start-end and return */
	if (start == end){
		printf("%d-%d \n", start, end);
		return;
	}
	
	/* test if there doesn't exist a path between start and end point */ 
	if (s->dist[end] == -1){
		printf("Error: Nonexisting path from %d to %d \n", start, end);
		return;
	}
	
	/* if start point and end point are different and there exists a path between them, follow steps below */
	
	n = graph_vertex_count(s->g);  /* get number of vetices in graph */
	path_list = malloc(n * sizeof(int));  /* initialize list for shortest path storing */
	
	/* store shortest path nodes in path_list from end point to start point */
	list_len = s->dist[end] + 1;
	path_list[0] = end;
	next = end;
	for (i = 1; i < list_len; i++){ 
		path_list[i] = s->parent[next];
		next = s->parent[next];
	}
	
	/* show path from start point to end point */
	for (i = list_len - 1; i > 0; i--){
		printf("%d-", path_list[i]);
	}
	printf("%d \n", path_list[i]);
	free(path_list);
	return;
}
