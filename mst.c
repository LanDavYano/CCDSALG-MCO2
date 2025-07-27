#include "mst.h"
void createMSTKruskals(Graph *g, int parent[], Edge edges[], Edge edges_mst[]){

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
        int s = getIndex(g, edges[o].source);
        int d = getIndex(g, edges[o].dest);
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
}


void printGraph(Graph *g, Edge edges_mst[], int edges_mst_count){

    int l, i;

    //prints graph header
    printf("G = {V, E}\n");

    //prints all the vertices
    printf("V = {");
    for(l=0;l<g->vertexCount;l++){
        printf("%s, ",g->vertices[l].name);
    }
    printf("}");

    printf("E= {\n");
        for(i=0;i<edges_mst_count;i++){
            printf("(%s, %s, %d),\n",edges_mst[i].source, edges_mst[i].dest, edges_mst[i].weight );
        }
    printf("}\n");
}

/* sorting the edge by weight and lexicographically source first*/
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


/* CREATING THE SET */
void createSet(int vertexCount) {
    for (int k = 0; k < vertexCount; k++) {
        parent[k] = k;
    }
}

// returning the root of the one you are adding to
int findRoot(int x){

    if(parent[x] != x){
        return findRoot(x);
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
