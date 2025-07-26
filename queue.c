#include "queue.h"

void createQueue(Queue *q){
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}

bool enqueue(Queue *q, const char* name){
    bool status = false;
    if (q->size < MAX)
    {
        strcpy(q->data[q->tail], name);
        q->tail = (q->tail + 1) % MAX;
        q->size++;
        status = !status;
    }
    return status;   
}

bool dequeue(Queue *q, char* name){
    bool status = false;
    if (q->size > 0)
    {
        strcpy(name, q->data[q->head]);
        q->head = (q->head + 1) % MAX;
        q->size--;
        status = !status;
    }
    return status; 
}

bool queueHead(Queue *q, char* name){
    bool status = false;
    if (q->size > 0)
    {
        strcpy(name, q->data[q->head]);
        status = !status;
    }
    return status;
}

bool queueTail(Queue *q, char* name){
    bool status = false;
    int lastValidIndex;
    if (q->size > 0)
    {
        lastValidIndex = (q->tail - 1 + MAX) % MAX;
        strcpy(name, q->data[lastValidIndex]);
        status = !status;
    }
    return status;
}

bool queueEmpty(Queue *q){
    bool status = false;
    if (q->size == 0)
    {
        status = !status;
    }
    return status;
}

bool queueFull(Queue *q){
    bool status = false;
    if (q->size == MAX)
    {
        status = !status;
    }
    return status;
}