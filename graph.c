#include "graph.h"

void initialzeGraph(Graph *g){
    int i, j;
    g->vertexCount = 0;
    for (i = 0; i < MAX_VERTICES; i++){
        g->vertices[i].exists = 0;
        for (j = 0; j < MAX_VERTICES; j++){
            g->adj[i][j] = 0;
            g->weight[i][j] = 0;
        }
    }
}

int getIndex(Graph *g, const char* name){
    int i;
    for (i = 0; i < g->vertexCount; i++){
        if (strcasecmp(g->vertices[i].name, name) == 0){
            return i;
        }
    }
    return -1;
}

void addVertex(Graph *g, const char* name){
    int index = getIndex(g, name);

    if (index == -1 && g->vertexCount < MAX_VERTICES){
        strcpy(g->vertices[g->vertexCount].name, name);
        g->vertices[g->vertexCount++].exists = 1;
    }
}


void addEdge(Graph *g, const char* source, const char* dest, int w)
{
    int i = getIndex(g, source);
    int j = getIndex(g, dest);

    if (i != -1 && j != -1){
        g->adj[i][j] = g->adj[j][i] = 1;
        g->weight[i][j] = g->weight[j][i] = w;
    }
}

int checkDegree(Graph *g, const char* name)
{
    int index = getIndex(g, name);
    int degreeCtr = 0;
    int i;
    
    if (index != -1){
        for (i = 0; i < g->vertexCount; i++)
        {
            degreeCtr += g->adj[index][i];
        }
    }
    return degreeCtr;
}

int checkEdge(Graph *g, const char* source, const char* dest)
{
    int i = getIndex(g, source);
    int j = getIndex(g, dest);

    return (g->adj[i][j] == 1 && g->adj[j][i] == 1) ? 1 : 0;
}