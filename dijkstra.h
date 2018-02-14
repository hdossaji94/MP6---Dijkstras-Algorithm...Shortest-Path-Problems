/* dijsktra.h 
 * dijkstra: Dijkstra's Algorithm and Graphs
 * ECE 223, Fall 2015
 * Huzefa Dossaji 
 * hdossaj
 *
 */

//vertices structure
struct Adjacent_Node{
	int num;
	double weight;
	struct Adjacent_Node* next;

};

//structure for graph types 3 when location is needed to produce weight
struct location{
	double x;
	double y;
};

struct information{
	int adjacent_vertices; 
};

// structred to hold all data coming out of dijsktra's algorithm or the shortest path algorithm
typedef struct aglorithm_data{
	double dist_ad;
	int pred_ad;

}data;

// points to first adjacent node in each vertice array
struct Adjacent_List{
	struct Adjacent_Node* head;

};

// graph that contains all vertices and hold information of the graph
struct Graph{
	
	int vertices; 
	int edges; 
	struct Adjacent_List* array;

};


struct Adjacent_Node* NewNodeAdj(int num, double weight);
void addEdge(struct Graph* graph, int link_source, int link_num, double link_weight);
struct Graph* newGraph(int vertices);

void destroy_graph(struct Graph* graph);

//auxillary function to help out graph part 2. or -g 2. 
double weight_funct(int i,int j);

void graph_debug_print(struct Graph* graph);


double weight_funct_g3(double distance, double C); //auxillary function to help out creategraph_g3

//shortest path function
int SPath(struct Graph* graph, int s, int d, data* dat);

//remove edge function
void graph_edge_remove(struct Graph* graph, int St_edge, int End_edge);


