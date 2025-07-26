#include "stack.h"

void createStack(Stack *s){
    s->top = -1;
}

bool push(Stack *s, const char* name){
    bool status = false;
    if (s->top < MAX - 1)
    {
        strcpy(s->items[++s->top], name);
        status = !status;
    }
    return status;
}

bool pop(Stack *s, char* name){
    bool status = false;
    if (s->top >= 0)
    {
        strcpy(name, s->items[s->top--]);
        status = !status;
    }
    return status;
}

bool topOfStack(Stack *s, char* name){
    bool status = false;
    if (s->top >= 0)
    {
        strcpy(name, s->items[s->top]);
        status = !status;
    }
    return status;
}

bool StackEmpty(Stack *s){
    bool status = false;
    if (s->top == -1)
    {
        status = !status;
    }
    return status;
}

bool StackFull(Stack *s){
    bool status = false;
    if (s->top == MAX - 1)
    {
        status = !status;
    }
    return status;
}