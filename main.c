#include "graph.h"
#include "graphOpps.h"
#include "mst.h"

int main(){

    //initializing the graph
    Graph g;
    g.vertexCount = 0;
    initialzeGraph(&g);

    int input;
                
    //for command 1 & 4 AddVertex GetDegree
    char vertexName[MAX_NAME_LEN];

    //for command 2 & 5 AddEdge CheckEdge 
    char vertex_source[MAX_NAME_LEN];
    char vertex_dest[MAX_NAME_LEN];
    int edge_weight;



    printf("Enter a command: ");
    while(fscanf("%d",&input) == 1){

        if(input == 11){
            continue;
        }

        if(input == 1){
            fscanf(stdin, "%s", vertexName);
            //adding the vertex
            addVertex(&g, vertexName);
        }else if(input == 2){
            fscanf(stdin, "%s", vertex_source);
            fscanf(stdin, "%s", vertex_dest);
            fscanf(stdin, "%d", edge_weight);
            //adding the edge
            addEdge(&g, vertex_source,vertex_dest,edge_weight);
        }else if(input == 3){
            fscanf(stdin, "%s", vertexName);
            //getting the degree
            checkDegree(&g, vertexName);
        }else if(input == 4){
            fscanf(stdin, "%s", vertex_source);
            fscanf(stdin, "%s", vertex_dest);
            checkEdge(&g,vertex_source,vertex_dest);
        }else if(input == 4){
            fscanf(stdin, "%s", vertex_source);
            fscanf(stdin, "%s", vertex_dest);
            fscanf(stdin, "%d", edge_weight);
        }

    }

    return 0;
}