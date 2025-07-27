#ifndef GRAPH_H
#define GRAPH_H

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


//need it for kruskals algoriothims
typedef struct {
    char source[50];
    char dest[50];
    int weight;
} Edge;

void initialzeGraph(Graph *g);
int getIndex(Graph *g, const char* name);
void addVertex(Graph *g, const char* name);
void addEdge(Graph *g, const char* source, const char* dest, int w);
int checkDegree(Graph *g, const char* name);
int checkEdge(Graph *g, const char* source, const char* dest);

#endif
