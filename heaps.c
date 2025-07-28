#include "heaps.h"
#include <stdbool.h>

void createHeap(MinHeap *heap){
    heap->heapSize = 0;
}

int parentIndex(int index){
    if (index > 0)
    {
        return (index - 1) / 2;
    }
    return -1;
}

int leftChild(int index){
    return 2 * index + 1;
}

int rightChild(int index){
    return 2 * index + 2;
}

// check if left child is smaller, return true if yes
bool checkLeftChild(MinHeap *heap, int index){
    int left = leftChild(index);
    if (left < heap->heapSize && heap->heapData[left].weight < heap->heapData[index].weight){
        return true;
    }

    return false;
}

// check if right child is smaller, return true if yes
bool checkRightChild(MinHeap *heap, int index){
    int right = rightChild(index);
    if (right < heap->heapSize && heap->heapData[right].weight < heap->heapData[index].weight){
        return true;
    }

    return false;
}

bool swapNodes(node *less, node *greater){
    node temp = *less;
    *less = *greater;
    *greater = temp;
    return true;
}

bool minHeapify(MinHeap *heap, int index){
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (checkLeftChild(heap, index)) {
        smallest = left;
    }

    else if (checkRightChild(heap, index)) {
        smallest = right;
    }

    if (smallest != index) {
        swapNodes(&heap->heapData[index], &heap->heapData[smallest]);
        minHeapify(heap, smallest);
        return true;
    }
    return false;
}

bool addNode(MinHeap *heap, node newNode){
    if (heap->heapSize >= MAX_VERTICES){
        return false;
    }

    int finder = heap->heapSize;
    heap->heapData[finder].index = newNode.index;
    heap->heapData[finder].weight = newNode.weight;
    heap->heapSize++;

    while (finder != 0 && heap->heapData[parentIndex(finder)].weight > heap->heapData[finder].weight){
        swapNodes(&heap->heapData[finder], &heap->heapData[parentIndex(finder)]);
        finder = parentIndex(finder);
    }
    
    return true;  // Added missing return statement
}

bool isHeapEmpty(MinHeap *heap){
    return heap->heapSize == 0;
}

node getMin(MinHeap *heap){
    node errorNode;
    node minNode;
    errorNode.index = -1;
    errorNode.weight = MAX_VERTICES;
    
    if (isHeapEmpty(heap)){
        return errorNode;
    }

    else if (heap->heapSize == 1){
        heap->heapSize--;
        return heap->heapData[0];
    }

    minNode = heap->heapData[0];
    heap->heapData[0] = heap->heapData[heap->heapSize - 1];
    heap->heapSize--;
    minHeapify(heap, 0);
    return minNode;

}

bool nodeExist(MinHeap *heap, int index){
    for (int i = 0; i < heap->heapSize; i++) {
        if (heap->heapData[i].index == index) {
            return true;
        }
    }

    return false;
}