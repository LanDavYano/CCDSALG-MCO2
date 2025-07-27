#include "graph.h"
#include "graphOpps.h"

typedef struct {
    char source[50];
    char dest[50];
    int weight;
} Edge;



void createMSTKruskals(Graph *g, int[] parent, Edge edges, Edge edges_mst);
void printGraph(Graph *g, Edge edges_mst[]);
void edgeSorter(Edge edges[], int edgeCount);
void createSet(int vertexCount);
int findRoot(int x);
void mergeSet(int p, int v);
int getIndex(Graph *g, char *name);