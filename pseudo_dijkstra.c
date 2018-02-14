/* C Programs from Chapter 10 of
 * Data Structures, Algorithms and Software Principles in C
 * by Thomas A. Standish
 */

/* Inputs:
 *     source:  the source vertex in the set V of vertices
 *     G:       a graph data structure that includes at least
 *         a.  count of number of vertices in the set V
 *         b.  either an adjacency matrix or adjacency lists
 *
 *           The code below assumes G contains a pointer to the matrix 
 *           T[ link_source ] [ link_destination]
 *           but modifying the code to use adjacency lists is easy
 *
 * Outputs:
 *     ShortestDistance[]: an array for the path cost to each vertex from the 
 *                         source on the shortest path
 *     Predecessor[]:  an array for the predecessor vertex (or the upsteam
 *                     neighbor) on the shortest path to each vertex
 */
  
void ShortestPath(G, source)
{
    // W is a set indicating which vertices have been confirmed, that is,
    //   the vertices for which we have found the shortest distance

    // Initialize W and ShortestDistance[u] as follows:
    W = {source};
    ShortestDistance[source] = 0;
    for (each u in V - {source} ) {
        ShortestDistance[u] = T[source][u];
    }

    // repeatedly enlarge W until W includes all vertices in V 
    while (W != V) {
     
        // find the vertex w in V - W at the minimum distance from source
        MinDistance = 'infinity'; 
        w = 'invalid vertex';
        for (each v in V - W) {
            if (ShortestDistance[v] < MinDistance) {
                MinDistance = ShortestDistance[v];
                w = v;
            }
        }

        // if a vertex w was found, add w to W, the confirmed set
        W = W union {w};

        // update the shortest distances to vertices in V - W via w 
        for (each u in V - W) {
            // if vertex u is a neighbor of w
            if (T[w][u] < 'infinity') {
                cost_to_u_via_w = ShortestDistance[w] + T[w][u];
                if (cost_to_u_via_w < ShortestDistance[u]) {
                    ShortestDistance[u] = cost_to_u_via_w;
                }
            }
        }
    }
}

int ShortestPath(struct Graph* graph, int s, int d, struct algorithm_data *data){
	
	double DistanceShort[graph->vertices];
	int pred[graph->vertices];
	int confirmed[graph->vertices];
	int conf_total = 0;
	double Distance_Min;
	int vertM;
	int a;
	
	struct Adjacent_Node* rover; 
	
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
		pred[rover->num] = graph->array[s].head->num;
		rover=rover->next;
	
	}
	
	while(conf+total != graph->vertices){
		Distance_Min = DBL_MAX;
		vertM = -1;
		for(a=0;a<graph->size; a++){
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
	
	
	
	rover = graph->array[vertM]->head;
	while(rover != NULL){
		if(DistanceShort[rover->num] > rover->weight + DistanceShort[graph->array[vertM]->head->num ){
			DistanceShort[rover->num] = rover->weight + DistanceShort[graph->array[vertM]->head->num;
			pred[rover->num] = graph->array[vertM]->head->num;
		}  
		rover = rover->next;
	}
	}else{
		break;
	}
   }
////////
	for(a=0;a<graph->vertices;a++){
		if(confirmed[a]==0){
			assert(DistanceShort[a] == DBL_MAX)
		}
	}
///////	
	if(confirmed[d] == 0){
		printf("No Path exists from vertex %d to vertex %d\n", s, d);
	
	}else{
		a = d;
		printf("cost: %f Path:", DistanceShort[d]);
		pritnf("%d", a);
		while(a!=s){
			printf("<-%d", pred[a]);
			a = pred[a];
		}
		printf("\n");
	 }
//////	      
	      for(a=0; a<graph->vertices; a++){
	      	data[a]->dist_ad = DistanceShort[a];
	      	data[a]->pred_ad = pred[a];
	      }
	      /*
	      printf("Vertex    |Cost    |Pre    |Confirm\n");
	      for(a=0;a<graph->vertices;a++){
	      	printf("%12d|%12.2f|%12d|%12d\n", a, DistanceShort[a], pred[a], confirmed[a]);
	      }*/
	      
	      if(confirmed[d] == 0){
	      	return 0;
	      }
	      return 1;
	
	}

  


