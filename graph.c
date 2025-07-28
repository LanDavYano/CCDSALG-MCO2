#include "graph.h"

void initializeGraph(Graph *g){
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

void checkDegree(Graph *g, const char* name)
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

    printf("%d", degreeCtr);
}

int checkEdge(Graph *g, const char* source, const char* dest)
{
    int i = getIndex(g, source);
    int j = getIndex(g, dest);

    return (g->adj[i][j] == 1 && g->adj[j][i] == 1) ? 1 : 0;
}

void printGraph(Graph *g) {
    int i, j, edgeCount = 0;
    char *u, *v;
    char names[MAX_VERTICES][MAX_NAME_LEN], t[MAX_NAME_LEN];
    Edges tmp, edges[MAX_VERTICES];

    // Copy vertex names
    for (i = 0; i < g->vertexCount; i++) {
        strcpy(names[i], g->vertices[i].name);
    }

    // Sort vertex names alphabetically
    for (i = 0; i < g->vertexCount - 1; i++) {
        for (j = i + 1; j < g->vertexCount; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                strcpy(t, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], t);
            }
        }
    }

    // Extract and normalize edges (u < v) for consistent ordering
    for (i = 0; i < g->vertexCount; i++) {
        for (j = i + 1; j < g->vertexCount; j++) {
            if (g->adj[i][j]) {
                u = g->vertices[i].name;
                v = g->vertices[j].name;

                if (strcmp(u, v) > 0) {
                    strcpy(edges[edgeCount].u, v);
                    strcpy(edges[edgeCount].v, u);
                } else {
                    strcpy(edges[edgeCount].u, u);
                    strcpy(edges[edgeCount].v, v);
                }

                edges[edgeCount++].weight = g->weight[i][j];
            }
        }
    }

    // Sort edges lexicographically by (u, v)
    for (i = 0; i < edgeCount - 1; i++) {
        for (j = i + 1; j < edgeCount; j++) {
            if (strcmp(edges[i].u, edges[j].u) > 0 ||
                (strcmp(edges[i].u, edges[j].u) == 0 && strcmp(edges[i].v, edges[j].v) > 0)) {
                tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }

    // Print G = (V, E)
    printf("G = (V, E)\n");

    // Print sorted vertices
    printf("V = {");
    for (i = 0; i < g->vertexCount; i++) {
        printf("%s", names[i]);
        if (i < g->vertexCount - 1) {
            printf(", ");
        }
    }
    printf("}\n");

    // Print sorted edges
    printf("E= {\n");
    for (i = 0; i < edgeCount; i++) {
        printf("   (%s, %s, %d)", edges[i].u, edges[i].v, edges[i].weight);
        if (i < edgeCount - 1) {
            printf(",\n");
        }
    }
    printf("\n}\n");
}