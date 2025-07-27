#ifndef GRAPHOPPS_H
#define GRAPHOPPS_H
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void breadthFirst(const char* key, Graph *g);
void depthFirst(Graph *g, const char* start);
void pathCheck(Graph *g, const char* startVertex, const char* targetVertex);
void minSpanTree();
int shortestPath(Graph *g, const char* source, const char* destination);


#endif