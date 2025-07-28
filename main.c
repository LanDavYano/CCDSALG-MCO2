#include "graph.h";
#include "stack.h";
#include "queue.h";

int main(){

    //initializing the graph
    Graph g;
    initializeGraph(&g);

    int input;
                
    //for command 1 & 4 AddVertex GetDegree & BFS & DFS
    char vertexName[MAX_NAME_LEN];

    //for command 2 & 5 AddEdge CheckEdge 
    char vertex_source[MAX_NAME_LEN];
    char vertex_dest[MAX_NAME_LEN];
    int edge_weight;
    int edge;

    while(fscanf(stdin, "%d", &input) == 1){
        switch(input){
            case 1:
                fscanf(stdin, "%s", vertexName);
                //adding the vertex
                addVertex(&g, vertexName);
                printf("\n");
                break;
            
            case 2:
                fscanf(stdin, "%s %s %d", vertex_source, vertex_dest, &edge_weight);
                addEdge(&g, vertex_source, vertex_dest, edge_weight);
                printf("\n");
                break;

            case 3:
                fscanf(stdin, "%s", vertexName);
                checkDegree(&g, vertexName);
                printf("\n\n");
                break;
            
            case 4:
                fscanf(stdin, "%s %s", vertex_source, vertex_dest);
                edge = checkEdge(&g,vertex_source,vertex_dest);
                printf("%d", edge);
                printf("\n\n");
                break;

            case 5:
                fscanf(stdin, "%s", vertex_source);
                breadthFirst(vertex_source, &g);
                printf("\n");
                break;

            case 6:
                fscanf(stdin, "%s", vertex_source);
                depthFirst(&g, vertex_source);
                printf("\n");
                break;

            case 7:
                fscanf(stdin, "%s %s", vertex_source, vertex_dest);
                pathCheck(&g, vertex_source, vertex_dest);
                printf("\n");
                break;

            case 8:
                kruskalMST(&g);
                printf("\n");
                break;

            case 9:
                fscanf(stdin, "%s %s", vertex_source, vertex_dest);
                shortestPath(&g, vertex_source, vertex_dest);
                printf("\n");
                break;

            case 10:
                printGraph(&g);
                printf("\n");
                break;

            case 11:
                return 0;
        }
    }
    return 0;
}