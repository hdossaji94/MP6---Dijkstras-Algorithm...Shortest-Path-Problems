/* lab6.c 
 * Lab6: Dijkstra's Algorithm and Graphs
 * ECE 223, Fall 2015
 * Huzefa Dossaji 
 * hdossaj
 *
 * PURPOSE: The function of this fule is to create the new graphs with the new vertices and edges
 * and also destroy and remove them as well. This file implements Dijsktra's algorithm with a 
 * directed linked list of vertices; 
 *	
 * ASSUMPTION: User would like a directed linked list
 *
 * BUGS: THERE ARE NO BUGS DETECTED EVEN WITH ALL MY EXTENSIVE TESTING
 *
 */


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>

#include "dijkstra.h"
#define PI 3.14159265358979323846

// structure function that creates a new Adjacent_Node or vertice with an edge
struct Adjacent_Node* NewNodeAdj(int num, double weight){
	struct Adjacent_Node* NodeNew = (struct Adjacent_Node*)malloc(sizeof(struct Adjacent_Node));
	NodeNew->num = num;
	NodeNew->weight = weight;
	
	NodeNew->next = NULL;
	return NodeNew; 

}

//structure function that creates the new graph that will point to the array of vertexes
struct Graph* newGraph(int vertices){
	struct Graph* NGraph = (struct Graph*) malloc(sizeof(struct Graph));
	NGraph->vertices = vertices; 
	
	NGraph->array = (struct Adjacent_List*)malloc(vertices*sizeof(struct Adjacent_List));
	
	int x;
	for(x=0; x<vertices; ++x){
		NGraph->array[x].head = NULL;
	}
	
	return NGraph;

}

// function that destroys the graph once finished. frees and and nulls all malloced memory
void destroy_graph(struct Graph* graph){
	struct Adjacent_Node* dest_rover = NULL;
	struct Adjacent_Node* prev = NULL; 
	int vert = graph->vertices; 
	int x;
	for(x=0; x<vert; x++){
		while((graph->array[x].head != dest_rover) && (graph->array[x].head != NULL) ){
			dest_rover = graph->array[x].head;
			
			while(dest_rover->next != NULL){
				prev = dest_rover; 
				dest_rover=dest_rover->next;
			}
				if(dest_rover != graph->array[x].head){
				free(dest_rover); 
				dest_rover = NULL;
				prev->next = NULL;
				}
		}
		
	}
	for (x=0; x<vert; x++){
		free(graph->array[x].head);
	}
	free(graph->array);
	free(graph);

}


// function that adds an edge to a new vertices in the graph. calls NewNodeAdj to create the new vertices
void addEdge(struct Graph* graph, int link_source, int link_num, double link_weight)
{
	struct Adjacent_Node* newN = NewNodeAdj(link_num, link_weight);

	newN->next = graph->array[link_source].head;
	
	graph->array[link_source].head = newN;
	
	graph->edges++;
	
	//only used if graph was undirected
	/*newN = NewNodeAdj(link_source);
	newN->next = graph->array[link_num].head;
	graph->array[link_num].head = newN;
*/
}

// auxillary function to help out graph part 2. or -g 2. returns the needed weight 
double weight_funct(int i,int j)
{
	return abs(i-j)+pow((i-j+2),2)+3*j;

}

// auxillary function to help out graph part 3 or -g3. returns the needed weight
double weight_funct_g3(double distance, double C)
{
	
	double M = log10(1+pow((1/C),2));
	double F = log10(1+pow((1/(distance+(C/1000))),2));
	return (M/F);

}

// function that implements dijkstra's algorithm. finds the shortest path between a source vertex and 
// a destination vertex and make sure it prints that with the weight it takes to get there. 
// also saves data to a data* dat that we can use that has information about the entire graph and its paths
int SPath(struct Graph* graph, int s, int d,  data* dat){

	double DistanceShort[graph->vertices];
	int pred[graph->vertices];
	int confirmed[graph->vertices];
	int conf_total = 0;
	double Distance_Min;
	int vertM;
	int a;
	
	// rover vertex
	struct Adjacent_Node* rover; 
	
	//initializing all values before the algorithm is taken place
	for(a=0; a<graph->vertices; a++){
		DistanceShort[a] = DBL_MAX;
		confirmed[a]= 0;
		pred[a] = -1; 
	}

	DistanceShort[s] = 0;
	confirmed[s] = 1;
	conf_total++;
	rover = graph->array[s].head;

	while(rover!=NULL){
		DistanceShort[rover->num] = rover->weight;
		pred[rover->num] = s;
		rover=rover->next;
	}

	while(conf_total != graph->vertices){
		Distance_Min = DBL_MAX;
		vertM = -1;
		for(a=0;a<graph->vertices; a++){
			if(DistanceShort[a] < Distance_Min){
				if(confirmed[a] == 0){
					Distance_Min = DistanceShort[a];
					vertM = a;
				}
			}
		}
		
		if(vertM >= 0){
			confirmed[vertM] = 1;
			conf_total++;
			rover = graph->array[vertM].head;
			//comparing distances to find the shortest path and adding to the predescessor list 
			while(rover != NULL){
				if(DistanceShort[rover->num] > rover->weight + DistanceShort[vertM] )
				{
					DistanceShort[rover->num] = rover->weight + DistanceShort[vertM];
					pred[rover->num] = vertM;
				}  
				rover = rover->next;
			}
		}else break;
		
	}
	
	if(confirmed[d] == 0){
		printf("No Path exists from vertex %d to vertex %d\n", s, d);

	}else{
		a = d;
		printf("cost: %f Path:", DistanceShort[d]);
		printf("%d", a);
		while(a!=s){
			printf("<-%d", pred[a]);
			a = pred[a];
		}
		printf("\n");
	}
	//saves all relavent data such as predecessors and the path distance into the data structure	      
	for(a=0; a<graph->vertices; a++){
		dat[a].dist_ad = DistanceShort[a];
		dat[a].pred_ad = pred[a];
	}
	
	// if path was not found then function will return 0, else 1. 
	if(confirmed[d] == 0){
		return 0;
	}
	return 1;

}

// removes an edge from the graph given the start of the edge and the end. 
void graph_edge_remove(struct Graph* graph, int St_edge, int End_edge){
	
	struct Adjacent_Node * r1;
	struct Adjacent_Node * r2;
	
	r1 = graph->array[St_edge].head;
	if(r1->num == End_edge)
	{
		r2 = r1;
		r1 = r1->next;
		graph->array[St_edge].head = r1;
		free(r2);
		graph->edges--;
	}else
	{
		while(r1->next->num != End_edge){
			r1=r1->next;
		}
		r2 = r1->next; 
		r1->next=r2->next;
		free(r2);
		graph->edges--;
	}
}

// graph printing debugger to help the user visualize what is going on. turn on during verbose mode
void graph_debug_print(struct Graph* graph){
	int a;
	printf("\nSTART OF GRAPH\n");
	for(a=0; a<graph->vertices; ++a){
		struct Adjacent_Node* trav = graph->array[a].head;
		printf("\n Vertex %d \n head", a);
		while(trav){
			printf("-> %d ", trav->num);
			trav = trav->next;
		}
		printf("\n");

	}

}
