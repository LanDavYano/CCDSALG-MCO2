#ifndef MST_H
#define MST_H
#include "graph.h"
#include "graphOpps.h"
extern int parent[256];

typedef struct {
    char source[50];
    char dest[50];
    int weight;
} Edge;

int createMSTKruskal(Graph *g, int parentArray[], Edge edges[], Edge edges_mst[]);
void printMSTGraph(Graph *g, Edge edges_mst[], int edges_mst_count);
void edgeSorter(Edge edges[], int edgeCount);
void createSet(int vertexCount);
int findRoot(int x);
void mergeSet(int p, int v);
int getMSTIndex(Graph *g, char *name);
void kruskalMST(Graph *g);

#endif
