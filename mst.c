#include "mst.h"

int parent[256];  // Global variable definition

int createMSTKruskal(Graph *g, int parentArray[], Edge edges[], Edge edges_mst[]){

    //for the edge count
    int edgeCount = 0;
    //for the temp variable
    int edges_mst_count = 0;

    char *u, *v;
    int i,j;

    char names[MAX_VERTICES][MAX_NAME_LEN], t[MAX_NAME_LEN];
    Edge tmp;

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
                    strcpy(edges[edgeCount].source, v);
                    strcpy(edges[edgeCount].dest, u);
                } else {
                    strcpy(edges[edgeCount].source, u);
                    strcpy(edges[edgeCount].dest, v);
                }

                edges[edgeCount++].weight = g->weight[i][j];
            }
        }
    }

    // Sort edges lexicographically by (u, v)
    for (i = 0; i < edgeCount - 1; i++) {
        for (j = i + 1; j < edgeCount; j++) {
            if (strcmp(edges[i].source, edges[j].source) > 0 ||
                (strcmp(edges[i].source, edges[j].source) == 0 && strcmp(edges[i].dest, edges[j].dest) > 0)) {
                tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }

    //sorts the edge by weight and alphabetically
    edgeSorter(edges, edgeCount);

    //create the set of parents first to check if it creates a cycle
    createSet(parentArray, g->vertexCount);

    //now we build the MST
    for(int o = 0; o<edgeCount;o++){

        //getting the index passing a 
        int s = getMSTIndex(g, edges[o].source);
        int d = getMSTIndex(g, edges[o].dest);

        int rootS = findRoot(parentArray, s);
        int rootD = findRoot(parentArray, d);
   
        if(rootS != rootD){
            //adding the MST to the set
            mergeSet(parentArray, rootS,rootD);
                        
            //adding to the new edge array
            strcpy(edges_mst[edges_mst_count].source, edges[o].source);
            strcpy(edges_mst[edges_mst_count].dest, edges[o].dest);
            edges_mst[edges_mst_count].weight = edges[o].weight;

            //printf("THIS IS A PATH SOURCE %s DEST %s WEIGHT %d \n",edges_mst[edges_mst_count].source, edges_mst[edges_mst_count].dest,edges_mst[edges_mst_count].weight);

            edges_mst_count++;
        }
    }
    return edges_mst_count;
}

void printMSTGraph(Graph *g, Edge edges_mst[], int edges_mst_count){

    int l, i, j;
    char *u, *v, *temp;
    int totalWeight = 0;
    char names[MAX_VERTICES][MAX_NAME_LEN], t[MAX_NAME_LEN];

    //prints graph header
    printf("MST(G) = (V, E)\n");

    for (i = 0; i < g->vertexCount; i++){
        strcpy(names[i], g->vertices[i].name);
    }

    for (i = 0; i < g->vertexCount - 1; i++){
        for (j = i + 1; j < g->vertexCount; j++){
            if(strcmp(names[i], names[j]) > 0) {
                strcpy(t, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], t);
            }
        }
    }

    //prints all the vertices
    printf("V = {");
    for(l=0;l<g->vertexCount;l++){
        printf("%s",names[l]);
        if (l < g->vertexCount - 1){
            printf(", ");
        }
    }
    printf("}\n");

    //print the edge to edge
    printf("E= {\n");
        for(i=0;i<edges_mst_count;i++){
            u = edges_mst[i].source;
            v = edges_mst[i].dest; 

            printf("   (%s, %s, %d),\n", u, v, edges_mst[i].weight);
            totalWeight += edges_mst[i].weight;
        }

    printf("}\n");
    printf("Total Edge Weight: %d\n", totalWeight);
}

void edgeSorter(Edge edges[], int edgeCount) {
    int i, j;

    for (i = 0; i < edgeCount - 1; i++) {
        for (j = 0; j < edgeCount - i - 1; j++) {
            //Sort by source
            if (strcmp(edges[j].source, edges[j + 1].source) > 0) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;

            } else if (strcmp(edges[j].source, edges[j + 1].source) == 0 && strcmp(edges[j].dest, edges[j + 1].dest) > 0) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// CREATING THE SET 
void createSet(int parentArray[], int vertexCount) {
    for (int k = 0; k < vertexCount; k++) {
        parentArray[k] = k;
    }
}

// returning the root of the one you are adding to
int findRoot(int parentArray[], int x) {
    if (parentArray[x] != x) {
        parentArray[x] = findRoot(parentArray, parentArray[x]);
    }
    return parentArray[x];
}

// void mergeSet(int parentArray[], int rootA, int rootB) {
//     parentArray[rootB] = rootA;  // directly merge rootB into rootA
// }

//gets the index of the struct
void mergeSet(int parentArray[], int rootA, int rootB) {
    if (rootA < rootB)
        parentArray[rootB] = rootA;
    else
        parentArray[rootA] = rootB;
}


int getMSTIndex(Graph *g, char *name) {
    for (int i = 0; i < g->vertexCount; i++) {
        if (strcmp(g->vertices[i].name, name) == 0) {
            return i;  // Found a match
        }
    }
    return -1;  // Not found
}

void kruskalMST(Graph *g){
    Edge edges[MAX_VERTICES];
    Edge edges_mst[MAX_VERTICES];
    int edges_mst_count = 0;

    edges_mst_count = createMSTKruskal(g, parent, edges, edges_mst);
       
    printMSTGraph(g, edges_mst, edges_mst_count);
}