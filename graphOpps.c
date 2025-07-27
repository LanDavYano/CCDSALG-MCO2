#include "graphOpps.h"

void breadthFirst(const char* key, Graph *g){
    Queue BFS;
    Queue search;
    char visited[256][256];
    int visitedCount = 0;
    char cur[256];
    char dequeued[256];
    char adjacent[256][256];
    char temp[256];
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

    // While search stack is not empty
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




int shortestPath(Graph *g, const char* source, const char* destination) {
    int sourceIndex, destIndex, i, j, minIndex;
    int dist[256];           /* Distance from source to each vertex */
    int visited[256];        /* Track visited vertices */
    int parent[256];         /* Track parent of each vertex for path reconstruction */
    int minDist, currentDist;
    char path[256][256];     /* Store the actual path */
    int pathLength;
    
    sourceIndex = getIndex(g, source);
    destIndex = getIndex(g, destination);
    
    if (sourceIndex == -1 || destIndex == -1) {
        printf("Source or destination vertex not found\n");
        return -1;
    }

    for (i = 0; i < g->vertexCount; i++) {
        dist[i] = 256;     
        visited[i] = 0;      
        parent[i] = -1;        
    }
    
    dist[sourceIndex] = 0;
    
    for (i = 0; i < g->vertexCount; i++) {
        minDist = 256;
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
    
    if (dist[destIndex] == 256) {
        printf("No path found from %s to %s\n", source, destination);
        return -1;
    }
    
    /* Reconstruct the path */
    pathLength = 0;
    int current = destIndex;
    
    /* Build path backwards from destination to source */
    while (current != -1) {
        strcpy(path[pathLength], g->vertices[current].name);
        pathLength++;
        current = parent[current];
    }
    
    /* Print the path in forward direction */
    printf("%s", path[pathLength - 1]);  /* Start with source */
    for (i = pathLength - 2; i >= 0; i--) {
        printf(" -> %s", path[i]);
    }
    printf("; Total edge cost = %d\n", dist[destIndex]);
    
    return dist[destIndex];
}

function minSpanTree(Graph *g){
    char adjacent[256][256];
    char temp[256];
    int adjacentCount;
    int alreadyVisited;
    int i, j;


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

}