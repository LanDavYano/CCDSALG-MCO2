
#include "graph.h"
#include "graphOpps.h"
int parent[256];

typedef struct {
    char source[50];
    char dest[50];
    int weight;
} Edge;



void createMSTKruskals(Graph *g, int parent[], Edge edges[], Edge edges_mst[]);
void printGraph(Graph *g, Edge edges_mst[], int edges_mst_count);
void edgeSorter(Edge edges[], int edgeCount);
void createSet(int vertexCount);
int findRoot(int x);
void mergeSet(int p, int v);
int getMSTIndex(Graph *g, char *name);