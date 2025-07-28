#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 256
#define MAX_VERTICES 256

typedef struct {
    char name[MAX_NAME_LEN];
    int exists;
} Vertex;

typedef struct {
    Vertex vertices[MAX_VERTICES];
    int adj[MAX_VERTICES][MAX_VERTICES];
    int weight[MAX_VERTICES][MAX_VERTICES];
    int vertexCount;
} Graph;

typedef struct {
    char u[MAX_NAME_LEN], v[MAX_NAME_LEN];
    int weight;
} Edges;

void initializeGraph(Graph *g);
int getIndex(Graph *g, const char* name);
void addVertex(Graph *g, const char* name);
void addEdge(Graph *g, const char* source, const char* dest, int w);
void checkDegree(Graph *g, const char* name);
int checkEdge(Graph *g, const char* source, const char* dest);
void printGraph(Graph *g);

#endif
