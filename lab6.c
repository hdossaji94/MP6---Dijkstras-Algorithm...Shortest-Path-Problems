/* lab6.c 
 * Lab6: Dijkstra's Algorithm and Graphs
 * ECE 223, Fall 2015
 * Huzefa Dossaji 
 * hdossaj
 * 
 * PURPOSE: The purpose of this file is to create a module for the different graph types and Dijsktra's algorithm
 * Unit drivers, graph types, and graph operations are all implemented in this file. Certain commands can 
 * activate them
 *
 * ASSUMPTION: User is able to give correct commands to the command line
 *
 * BUGS: THERE ARE NO BUGS DETECTED EVEN WITH ALL MY EXTENSIVE TESTING
 *
 * This file contains drivers to test the diksktra.c package.
 *
 * 	    case 'g': Graph_Type = atoi(optarg);        break;
 *          case 'n': Num_Vertices = atoi(optarg);      break;
 *          case 'a': Adj_Vertices = atoi(optarg);      break;
 *          case 'h': Graph_Operation = atoi(optarg);	break;
 *          case 's': Source_Vertex = atoi(optarg);  	break;
 *          case 'd': Dest_Vertex = atoi(optarg); 	break;
 *          case 'u': UnitNumber = atoi(optarg);   	break;
 *          case 'v': Verbose = TRUE;              	break;
 *          case 'r': RandomTest = TRUE;           	break;
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <float.h>

#include "dijkstra.h"



#define TRUE 1
#define FALSE 0

#define PI 3.14159265358979323846

/* Global variables for command line parameters */
int UnitNumber = -1;
int Graph_Type = -1;
int Num_Vertices = -1;
int Adj_Vertices = -1;
int Graph_Operation = -1;
int Source_Vertex = -1;
int Dest_Vertex = -1;
int Seed = 1234567;
int Verbose = FALSE;
int RandomTest = FALSE;


/* prototypes for functions in this file only */
void getCommandLine(int argc, char **argv);
void Graph_Operation_Function(struct Graph* graph);


int main(int argc, char **argv)
{
    int go = 0;
    getCommandLine(argc, argv);
    printf("Seed: %d\n", Seed);
    srand48(Seed);
    struct Graph* graph;
    // structures that are malloced to use for holding information such as location
    struct location* plot = (struct location*)malloc(Num_Vertices*sizeof(struct location));
    struct information* info = (struct information*)malloc(Num_Vertices*sizeof(struct information));

		//first unit driver tests to see if graph is created correctly with random adds
	    if (UnitNumber == 0)                        /* enabled with -u flag */
	    {	go = 1;
			    	
		    int V = 7;
		    Num_Vertices = V;
		    graph = newGraph(V);
		    
		    addEdge(graph, 0, 2, 10);
		    addEdge(graph, 0, 1, 5);
		    addEdge(graph, 0, 5, 4);
		    addEdge(graph, 1, 0, 2);
		    addEdge(graph, 1, 3, 7);
		    addEdge(graph, 1, 5, 6);
		    addEdge(graph, 2, 6, 4);
		    addEdge(graph, 3, 4, 8);
		 
		    
		    graph_debug_print(graph);
		 

	    }
	    // second unit driver tests to see if program can correctly remove edges after they are added
	    if(UnitNumber == 1){
	    	go = 1;
	    	int V = 5;
	    	Num_Vertices = V;
	    	graph = newGraph(V);
	    	
	    	addEdge(graph, 0, 2, 10);
		addEdge(graph, 0, 1, 5);
		addEdge(graph, 0, 4, 4);
		addEdge(graph, 4, 3, 2);
		addEdge(graph, 1, 2, 2);
		addEdge(graph, 1, 0, 2);
		addEdge(graph, 3, 0, 2);
		addEdge(graph, 2, 4, 2);										
		graph_debug_print(graph);
		graph_edge_remove(graph, 0, 1);
		graph_debug_print(graph);
		graph_edge_remove(graph, 0, 2);
		graph_edge_remove(graph, 0, 4);		
		graph_debug_print(graph);
			    
	    }
	   
	    // graph type 1 creates the graph given to us in the pdf. 
	    if(Graph_Type == 1)
	    {
	    	go = 1;
	    	int V = 7;
	    	Num_Vertices = V;
		graph = newGraph(V);
		
	    	addEdge(graph, 1, 2, 3);
	    	addEdge(graph, 1, 6, 5);
	    	addEdge(graph, 2, 3, 7);
	    	addEdge(graph, 2, 4, 3);
	    	addEdge(graph, 2, 6, 10);
	    	addEdge(graph, 3, 4, 5);
	    	addEdge(graph, 3, 5, 1);
	    	addEdge(graph, 4, 5, 6);
	    	addEdge(graph, 5, 6, 7);
	    	addEdge(graph, 6, 0, 4);
	    	addEdge(graph, 6, 3, 8);
	    	addEdge(graph, 6, 4, 9);
	    	
	    	graph_debug_print(graph);
	    	

	    
	    }
	    // graph type 2 creates a strongly connected graphs where all vertices have edges to each other
	    if(Graph_Type == 2)
	    {
	    	go = 1;
	    	int i,j;
	    	double w; 
		if(Num_Vertices == -1){
			printf("Please input a -n value number of vertices. \n");
			return 0;
		}
		graph = newGraph(Num_Vertices);
		for(i=0; i<Num_Vertices; i++){
			for(j=0; j<Num_Vertices; j++){
				if(i==j)
				{
					continue;
				}
				else{
					w = weight_funct(i,j);
					addEdge(graph, i, j, w); 
				}
			}
		}
		if(Verbose){
		graph_debug_print(graph);
		}

	    }
	    
	    // graph type 3 makes use of a random graph where the weight is dependent on the vertices random location
	    // in the graph. 
	    if(Graph_Type == 3)
	    {	go = 1;
	    	if(Num_Vertices == -1 || Adj_Vertices == -1)
	    	{
			printf("Please input a value for the number of vertices and adjacent neighbors. \n");
			return 0;
		}
	    	double C = sqrt(Adj_Vertices/(Num_Vertices*PI));	
	    	double E;    
	    	int i,j;	
		graph = newGraph(Num_Vertices);
	    	
	    	
	    	for(i=0; i<Num_Vertices; i++){
	    		info[i].adjacent_vertices=0; 
	    	}
	    	
	    	plot[0].x = 0.0;
	    	plot[0].y = 0.5;
	    	plot[Num_Vertices-1].x = 1.0;
	    	plot[Num_Vertices-1].y = 0.5;
	    	for(i=1; i<Num_Vertices-1;i++){
	    		plot[i].x=drand48();
	    		plot[i].y=drand48();
	    	}
	    	for(i=0; i<Num_Vertices; i++){
	    		
			for(j=0; j<Num_Vertices; j++){
				if(i==j)
				{
					continue;
				}
				else if((sqrt(pow((plot[i].x - plot[j].x),2)+pow((plot[i].y - plot[j].y),2)))<=C){
					E = weight_funct_g3((sqrt(pow((plot[i].x - plot[j].x),2)+pow((plot[i].y - plot[j].y),2))), C);
					addEdge(graph, i, j, E); 
					info[i].adjacent_vertices++;
				}else
				{
					E = 1.0/0.0;
					addEdge(graph, i, j, E); 
				}
			}
		}

	    	
	    	int max = info[0].adjacent_vertices;
	    	int min = info[0].adjacent_vertices;
	    	double average;
	    	int sum=0;
	    	for(i=0; i<Num_Vertices; i++){
	    		sum = sum +info[i].adjacent_vertices;
	    		if(info[i].adjacent_vertices > max) {
	    			max = info[i].adjacent_vertices;
	    		}else if(info[i].adjacent_vertices < min){
	    			min = info[i].adjacent_vertices;
	    		}
	    	}
	    	average = sum/Num_Vertices;
	    	printf("# of Vertices - Average: %lf, Max: %d, Min: %d\n", average, max, min);
	    	
	    	if(Verbose){
			graph_debug_print(graph);
		}
	    
	    }
	    //conditional if a incorrect command key is inputted then the program will alert the user and 
	    // ask them input a correct one before an freeing can be done. if correct input is given then 
	    // program will go to the next graph operation function if a graph operation was inputted
	    if(go == 1){
	   Graph_Operation_Function(graph);
	  //freeing malloced memory
	   	free(plot);
	   	free(info);
	   // destroying graph after use
	   destroy_graph(graph);
	   }else{
	   	printf("Please input a correct command!\n");
	   }
	    return 0;
}

// function that holds the different graph operation types such as shortest path, network diamater
// and multiple link-disjoing paths
void Graph_Operation_Function(struct Graph* graph){
		//malloced structure type datas to hold the data when coming out of the shortest path aglortihm 
		data * dat = (data*)malloc(Num_Vertices*sizeof(data));
		data * copy = (data*)malloc(Num_Vertices*sizeof(data));
		int x, y, i;
		int conn;
		int connection=1;
		double max=0;
		int source;
		int dest;
		clock_t start, end;

//operation that simply calls the shortest path function to get the shortest path and weight of a soource and dest vertex		
	 if (Graph_Operation == 1){
	 	start = clock();
		SPath(graph, Source_Vertex, Dest_Vertex, dat);
		end = clock();
		printf("Clock Time: %g\n", ((double)(end-start))/CLOCKS_PER_SEC);
	 }
	 // operation that finds the largest path from the shortest paths. creating a boundary for a network in a sense
	 if (Graph_Operation == 2){
	 	 start = clock();
	 	for(x=0;x<Num_Vertices;x++){
	 		for(y=0;y<Num_Vertices; y++){
	 			if(x==y) continue;
	 			else{
	 			conn = SPath(graph, x, y, dat);
	 			if(conn == 0){
	 				connection = 0;
	 			}
	 			if((dat[y].dist_ad > max) && (dat[y].dist_ad != DBL_MAX)){
	 				
	 				max = dat[y].dist_ad;
	 				for(i=0; i<Num_Vertices; i++){
	 					copy[i].pred_ad = dat[i].pred_ad;
	 				}
	 				
	 				dest = y;
	 				source = x;
	 				}
	 			}
	 		}
	 	}
	 	end = clock();
		printf("Clock Time: %g\n", ((double)(end-start))/CLOCKS_PER_SEC);	 	
	 	printf("\n\n\nOUTPUT:\n");
	 	printf("cost: %f Path:", max);
		printf("%d", dest);
		while(dest!=source){
			printf("<-%d", copy[dest].pred_ad);
			dest = copy[dest].pred_ad;
		}
		if(connection == 1){
			printf("\nGraph is connected");
		}
		else{
			printf("\nGraph is not connected");
		}
		printf("\n");
	 }
	// operation that gets the shortest path from a source to a dest vertex, then removes the edges from 
	// that path and searches again to find a different path with heavier weight. it keeps doing this 
	// until no path is left between the two vertices. 	 
	 if(Graph_Operation == 3){
	 	SPath(graph, Source_Vertex, Dest_Vertex, dat);
	 	int d = Dest_Vertex;
	 	int s = Source_Vertex;
	 	int loop=1; 
	 while (loop == 1){	
		while(d!=s){
			graph_edge_remove(graph, dat[d].pred_ad, d);
			d = dat[d].pred_ad;
			if(Verbose){
				graph_debug_print(graph);
			}
		}
		d = Dest_Vertex;
	 	
	 	loop = SPath(graph, Source_Vertex, Dest_Vertex, dat);
	 }
	 }
	// freeing malloced data structures. 
	 	free(dat);
		free(copy);	 
	 

}


/* read in command line arguments and store in global variables for easy
 * access by other functions.
 */
void getCommandLine(int argc, char **argv)
{
    /* optopt--if an unknown option character is found
     * optind--index of next element in argv 
     * optarg--argument for option that requires argument 
     * "x:" colon after x means argument required
     */
    int c;
    int index;

    while ((c = getopt(argc, argv, "g:n:a:h:s:d:u:r:v")) != -1)
        switch(c) {
            case 'g': Graph_Type = atoi(optarg);        break;
            case 'n': Num_Vertices = atoi(optarg);      break;
            case 'a': Adj_Vertices = atoi(optarg);      break;
            case 'h': Graph_Operation = atoi(optarg);	break;
            case 's': Source_Vertex = atoi(optarg);  	break;
            case 'd': Dest_Vertex = atoi(optarg); 	break;
            case 'u': UnitNumber = atoi(optarg);   	break;
            case 'r': Seed = atoi(optarg);           	break;
            case 'v': Verbose = TRUE;              	break;
           
        }
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
}
