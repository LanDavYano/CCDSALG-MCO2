#ifndef HEAPS_H
#define HEAPS_H
#include "graph.h"
#include <stdbool.h>

typedef struct {
    int index;
    int weight;
} node;

typedef struct {
    node heapData[MAX_VERTICES];
    int heapSize;
} MinHeap;

void createHeap(MinHeap *heap);
int parentIndex(int index);
int leftChild(int index);
int rightChild(int index);
bool checkLeftChild(MinHeap *heap, int index);
bool checkRightChild(MinHeap *heap, int index);
bool swapNodes(node *less, node *greater);
bool minHeapify(MinHeap *heap, int index);
bool addNode(MinHeap *heap, node newNode);
bool isHeapEmpty(MinHeap *heap);
node getMin(MinHeap *heap);
bool nodeExist(MinHeap *heap, int index);

#endif