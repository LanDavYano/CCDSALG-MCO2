#include "mst.h"

int parent[256];  // Global variable definition

int createMSTKruskal(Graph *g, int parentArray[], Edge edges[], Edge edges_mst[]){

    // int parent[MAX_VERTICES]; // adjust size as needed
    // Edge edges[MAX_VERTICES * MAX_VERTICES];

    //for the edge count
    int edgeCount = 0;
    //for the temp variable
    int edges_mst_count = 0;

    for (int i = 0; i < g->vertexCount; i++) {
        for (int j = i + 1; j < g->vertexCount; j++) {
            if (g->adj[i][j]) {
                strcpy(edges[edgeCount].source, g->vertices[i].name); // SOURCES
                strcpy(edges[edgeCount].dest, g->vertices[j].name);   // DESTINATIONS
                edges[edgeCount].weight = g->weight[i][j];            // WEIGHT
                edgeCount++; 
            }
        }
    }

    //sorts the edge by weight and alphabetically
    edgeSorter(edges, edgeCount);

    //create the set of parents first to check if it creates a cycle
    createSet(g->vertexCount);

    //now we build the MST
    for(int o = 0; o<edgeCount;o++){

        //getting the index passing a 
        int s = getMSTIndex(g, edges[o].source);
        int d = getMSTIndex(g, edges[o].dest);
        //find muna kung ano result ng findRoot
        int rootS = findRoot(s);
        int rootD = findRoot(d);

        if(rootS != rootD){
            //adding the MST to the set
            mergeSet(rootS,rootD);
            //adding to the new edge array
            strcpy(edges_mst[edges_mst_count].source, edges[o].source);
            strcpy(edges_mst[edges_mst_count].dest, edges[o].dest);
            edges_mst[edges_mst_count].weight = edges[o].weight;
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

    printf("E= {\n");
        for(i=0;i<edges_mst_count;i++){
            u = edges_mst[i].source;
            v = edges_mst[i].dest;

            if (strcmp(u, v) > 0) {
                temp = u;
                u = v;
                v = temp;
            }    
        }
        if (i > 0){
            printf(",\n");
        }
        printf("   (%s, %s, %d)", u, v, edges_mst[i].weight);
        totalWeight += edges_mst[i].weight;
        
    printf("}\n");
    printf("Total Edge Weight: %d\n", totalWeight);
}

// sorting the edge by weight and lexicographically source first
void edgeSorter(Edge edges[], int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            //sort by weight first
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;

            } else if (edges[j].weight == edges[j + 1].weight) {

                //if its the same weight check if the source is greater than the edge
                if (strcmp(edges[j].source, edges[j + 1].source) > 0) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }

        }
    }
}


// CREATING THE SET 
void createSet(int vertexCount) {
    for (int k = 0; k < vertexCount; k++) {
        parent[k] = k;
    }
}

// returning the root of the one you are adding to
int findRoot(int x){
    if (x < 0 || x >= MAX_VERTICES) return -1;  
    if(parent[x] != x){
        return findRoot(parent[x]);
    }
    return x;
}
//merging the set/adding it to the MST
void mergeSet(int p, int v){
    parent[p] = v;
}

//gets the index of the struct
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
