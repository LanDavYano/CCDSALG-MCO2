#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <string.h>

#define MAX 256
#define MAX_NAME_LEN 256

typedef struct {
    int head, tail, size;
    char data[MAX][MAX_NAME_LEN];
} Queue;

void createQueue(Queue *q);
bool enqueue(Queue *q, const char* name);
bool dequeue(Queue *q, char* name);
bool queueHead(Queue *q, char* name);
bool queueTail(Queue *q, char* name);
bool queueEmpty(Queue *q);
bool queueFull(Queue *q);

#endif