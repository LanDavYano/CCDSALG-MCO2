#include "graphOpps.h"

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

void pathCheck(Graph *g, const char* startVertex, const char* targetVertex){
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

void shortestPath(Graph *g, const char* source, const char* dest){
    int sourceIndex, destIndex, i, j;
    int dist[MAX_VERTICES];               
    int parent[MAX_VERTICES];         
    char path[MAX_VERTICES][MAX_NAME_LEN];   
    int pathLength;
    int current;
    MinHeap heap;
    node currentNode;
    const int INFINITY = 999999;  
    
    sourceIndex = getIndex(g, source);
    destIndex = getIndex(g, dest);
    
    if (sourceIndex == -1 || destIndex == -1) {
        printf("Source or destination vertex not found\n");
        return;
    }

    // Initialize distances and parent array
    for (i = 0; i < g->vertexCount; i++) {
        dist[i] = INFINITY;      
        parent[i] = -1;        
    }

    // Distance from source to itself is 0
    dist[sourceIndex] = 0;

    // Create heap and add all vertices
    createHeap(&heap);
    for (i = 0; i < g->vertexCount; i++) {
        currentNode.index = i;
        currentNode.weight = dist[i];
        addNode(&heap, currentNode);
    }

    // Dijkstra's algorithm with heap
    while(!isHeapEmpty(&heap)) {
        // Get the node with minimum distance from heap
        currentNode = getMin(&heap);
        int indexOfCurrent = currentNode.index;

        // If we reached the destination, we can stop
        if (indexOfCurrent == destIndex) {
            break;
        }

        // If distance is infinity, remaining vertices are unreachable
        if (dist[indexOfCurrent] == INFINITY) {
            break;
        }

        // Update distances to adjacent vertices
        for (j = 0; j < g->vertexCount; j++) {
            // Check if there's an edge and vertex j is still in heap
            if (g->adj[indexOfCurrent][j] && nodeExist(&heap, j))
            {
                int distNew = dist[indexOfCurrent] + g->weight[indexOfCurrent][j];

                // If new path is shorter, update distance and parent
                if (distNew < dist[j]) {
                    dist[j] = distNew;
                    parent[j] = indexOfCurrent;
                    
                    // Update the heap by finding and updating the node
                    for (i = 0; i < heap.heapSize; i++) {
                        if (heap.heapData[i].index == j) {
                            heap.heapData[i].weight = distNew;
                            
                            // Bubble up to maintain heap property
                            int currentIdx = i;
                            while (currentIdx > 0) {
                                int parentIdx = (currentIdx - 1) / 2;
                                if (heap.heapData[parentIdx].weight <= heap.heapData[currentIdx].weight) {
                                    break; // Heap property satisfied
                                }
                                // Swap with parent
                                node temp = heap.heapData[currentIdx];
                                heap.heapData[currentIdx] = heap.heapData[parentIdx];
                                heap.heapData[parentIdx] = temp;
                                currentIdx = parentIdx;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    
    // Check if path exists
    if (dist[destIndex] == INFINITY) {
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
