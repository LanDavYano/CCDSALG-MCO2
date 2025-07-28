#ifndef MST_H
#define MST_H
#include "graph.h"
#include "graphOpps.h"
extern int parent[256];

typedef struct {
    char source[256];
    char dest[256];
    int weight;
} Edge;

int createMSTKruskal(Graph *g, int parentArray[], Edge edges[], Edge edges_mst[]);
void printMSTGraph(Graph *g, Edge edges_mst[], int edges_mst_count);
void edgeSorter(Edge edges[], int edgeCount);
void createSet(int parentArray[], int vertexCount);
int findRoot(int parentArray[], int x);
void mergeSet(int parentArray[], int a, int b);
int getMSTIndex(Graph *g, char *name);
void kruskalMST(Graph *g);

#endif
