#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <string.h>

#define MAX 256
#define MAX_NAME_LEN 256

typedef struct {
    int top;
    char items[MAX][MAX_NAME_LEN];
} Stack;

void createStack(Stack *s);
bool push(Stack *s, const char* name);
bool pop(Stack *s, char* name);
bool topOfStack(Stack *s, char* name);
bool StackEmpty(Stack *s);
bool StackFull(Stack *s);

#endif