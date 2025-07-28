#include "graphOpps.h"
int parent[256];

void breadthFirst(const char* key, Graph *g){
    Queue BFS;
    Queue search;
    char visited[MAX][MAX];
    int visitedCount = 0;
    char cur[MAX];
    char dequeued[MAX];
    char adjacent[MAX][MAX];
    char temp[MAX];
    int adjacentCount;
    int alreadyVisited;
    int i, j;
    
    createQueue(&BFS);
    createQueue(&search);

    /* Check if starting vertex exists */
    if (getIndex(g, key) == -1) {
        return;
    }

    /* Start by adding key to BFS queue and marking as visited */
    enqueue(&BFS, key);
    strcpy(visited[visitedCount++], key);
    printf("%s\n", key);
    
    /* Main BFS loop */
    while (!queueEmpty(&BFS)) {
        /* Get current vertex from BFS queue */
        if (!dequeue(&BFS, cur)) {
            break;
        }
        
        /* Reset adjacentCount for each vertex */
        adjacentCount = 0;
        
        /* Find all adjacent vertices that haven't been visited */
        for (i = 0; i < g->vertexCount; i++) {
            if (checkEdge(g, cur, g->vertices[i].name)) {
                /* Check if already visited */
                alreadyVisited = 0;
                for (j = 0; j < visitedCount; j++) {
                    if (strcmp(visited[j], g->vertices[i].name) == 0) {
                        alreadyVisited = 1;
                        break;
                    } 
                }
                
                /* If not visited, add to adjacent list */
                if (!alreadyVisited) {
                    strcpy(adjacent[adjacentCount++], g->vertices[i].name);
                }
            }
        }
        
        /* Sort adjacent vertices lexicographically (bubble sort) */
        for (i = 0; i < adjacentCount - 1; i++) {
            for (j = 0; j < adjacentCount - i - 1; j++) {
                if (strcmp(adjacent[j], adjacent[j+1]) > 0) {
                    strcpy(temp, adjacent[j]);
                    strcpy(adjacent[j], adjacent[j+1]);
                    strcpy(adjacent[j+1], temp);
                }
            }
        }

        /* Enqueue sorted adjacent vertices to search queue */
        for (i = 0; i < adjacentCount; i++) {
            enqueue(&search, adjacent[i]);
        }
        
        /* Transfer from search queue to BFS queue and mark as visited */
        while (!queueEmpty(&search)) {
            if (dequeue(&search, dequeued)) {
                enqueue(&BFS, dequeued);
                strcpy(visited[visitedCount++], dequeued);
                printf("%s\n", dequeued);
            }
        }
    }
}

void depthFirst(Graph *g, const char* start){
    int startingIndex, poppedIndex, countAdjVert, i, j, marked[MAX_VERTICES] = {0};
    char popped[MAX], adjacentVertices[MAX_VERTICES][MAX_NAME_LEN];
    Stack dfsStack;

    // Check if starting vertex exist in the graph
    startingIndex = getIndex(g, start);
    if (startingIndex == -1){
        printf("Starting vertex is not in the graph.\n");
        return;
    }
    
    // Create dfs stack
    createStack(&dfsStack);

    // push the starting vertex to stack
    push(&dfsStack, g->vertices[startingIndex].name);

    // While search stack is not empty
    while(!StackEmpty(&dfsStack)){
        // pop the stack
        pop(&dfsStack, popped);

        // get the index of the popped one
        poppedIndex = getIndex(g, popped);
        // check if the index of the popped on deson't exist in the graph or the index was already marked
        if (poppedIndex == -1 || marked[poppedIndex]){
            continue;// if true then continue to the next iteration
        }

        marked[poppedIndex] = 1;
        // print the popped one
        printf("%s\n", popped);

        // Reset counter for adjacent vertices 
        countAdjVert = 0;

        // check the neighbor 
        for (i = 0; i < g->vertexCount; i++){
            // check the one that are adjacent to the popped ones and check if it not marked
            if (g->adj[poppedIndex][i] && !marked[i]){
                // if adjacent and not marked then get that neighbor
                strcpy(adjacentVertices[countAdjVert++], g->vertices[i].name);
            }
        }
            
        // sort the neighbors using qsort in descending order
        qsort(adjacentVertices, countAdjVert, sizeof(adjacentVertices[0]), (int (*)(const void *, const void *))strcmp);
        // pcountAdjVert, sh all neighbors to stack
        for (j = countAdjVert - 1; j >= 0; j--){
            push(&dfsStack, adjacentVertices[j]);
        }
    }
}

void pathCheck(Graph *g, const char* startVertex, const char* targetVertex)
{
    int startingIndex, targetIndex, poppedIndex, i, marked[MAX_VERTICES] = {0};
    char popped[MAX];
    Stack stack;
    bool found = false;

    // Check if starting vertex exist in the graph
    startingIndex = getIndex(g, startVertex);
    targetIndex = getIndex(g, targetVertex);

    if (startingIndex == -1 || targetIndex == -1)
    {
        printf("0\n");
        return;
    }
    
    // Create stack
    createStack(&stack);

    // push the starting vertex to stack
    push(&stack, g->vertices[startingIndex].name);

    // While stack is not empty
    while(!StackEmpty(&stack))
    {
        // pop the stack
        pop(&stack, popped);

        // get the index of the popped one
        poppedIndex = getIndex(g, popped);
        // check if the index of the popped on deson't exist in the graph or the index was already marked
        if (poppedIndex == -1 || marked[poppedIndex])
        {
            continue;// if true then continue to the next iteration
        }

        marked[poppedIndex] = 1;
        // check if the poppedIndex is already at the targetIndex
        if (poppedIndex == targetIndex)
        {
            found = true;
        }
        
        // check the neighbor 
        for (i = 0; i < g->vertexCount; i++)
        {
            // check the one that are adjacent to the popped ones and check if it not marked
            if (g->adj[poppedIndex][i] && !marked[i])
            {
                // if adjacent and not marked then get that neighbor
                push(&stack, g->vertices[i].name);
            }
        }
    }

    if (found)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
} 

void shortestPath(Graph *g, const char* source, const char* dest) {
    int sourceIndex, destIndex, i, j, minIndex;
    int dist[MAX];           /* Distance from source to each vertex */
    int visited[MAX];        /* Track visited vertices */
    int parent[MAX];         /* Track parent of each vertex for path reconstruction */
    int minDist, currentDist;
    char path[MAX][MAX];     /* Store the actual path */
    int pathLength;
    int current;
    
    sourceIndex = getIndex(g, source);
    destIndex = getIndex(g, dest);
    
    if (sourceIndex == -1 || destIndex == -1) {
        printf("Source or destination vertex not found\n");
        return;
    }

    for (i = 0; i < g->vertexCount; i++) {
        dist[i] = MAX;     
        visited[i] = 0;      
        parent[i] = -1;        
    }
    
    dist[sourceIndex] = 0;
    
    for (i = 0; i < g->vertexCount; i++) {
        minDist = MAX;
        minIndex = -1;
        
        for (j = 0; j < g->vertexCount; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        
        if (minIndex == -1) {
            break;
        }
        
        visited[minIndex] = 1;
        
        if (minIndex == destIndex) {
            break;
        }

        for (j = 0; j < g->vertexCount; j++) {
            if (g->adj[minIndex][j] && !visited[j]) {
                currentDist = dist[minIndex] + g->weight[minIndex][j];
        
                if (currentDist < dist[j]) {
                    dist[j] = currentDist;
                    parent[j] = minIndex;  
                }
            }
        }
    }
    
    if (dist[destIndex] == MAX) {
        printf("No path found from %s to %s\n", source, dest);
        return;
    }

    if (minIndex == -1) {
        printf("No path found from %s to %s\n", source, dest);
        return;
    }
    
    // Reconstruct the path 
    pathLength = 0;
    current = destIndex;
    
    // Build path backwards from destination to source 
    while (current != -1) {
        strcpy(path[pathLength], g->vertices[current].name);
        pathLength++;
        current = parent[current];
    }
    
    // Print the path in forward direction 
    printf("%s", path[pathLength - 1]);  // Start with source 
    for (i = pathLength - 2; i >= 0; i--) {
        printf(" -> %s", path[i]);
    }
    printf("; Total edge cost = %d\n", dist[destIndex]);
    
}



/* creating the min-span tree*/
void createMSTKruskals(Graph *g, int[] parent, Edge edges, Edge edges_mst){

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
            strcpy(edges_mst[edges_mst_count].weight, edges[o].weight);
            edges_mst_count++;
        }
    }
}


void printGraph(Graph *g, Edge edges_mst[]){

    int l, i;

    //prints graph header
    printf("G = {V, E}\n");

    //prints all the vertices
    printf("V = {");
    for(l=0;l<g->vertexCount;l++){
        printf("%s, ",g[0]->vertices[l].name);
    }
    printf("}");

    printf("E= {\n");
        for(i=0;i<edges_mst.length;i++){
            printf("(%s, %s, %d),\n",edges_mst[i].source,edges_mst[i].dest,edges_mst[i].weight )
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
int getIndex(Graph *g, char *name) {
    for (int i = 0; i < g->vertexCount; i++) {
        if (strcmp(g->vertices[i].name, name) == 0) {
            return i;  // Found a match
        }
    }
    return -1;  // Not found
}
