#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define SDATA_TYPE char

typedef struct {
    SDATA_TYPE* data;
    int capacity;
    int top;
} Stack;

Stack* stack_create(int capacity);  // Returns NULL on failure:
int stack_get_capacity(Stack* s);   // Return -1 if S is NULL
int stack_get_size(Stack* s);       // Return -1 if S is NULL
bool stack_is_empty(Stack* s);      // Return false if S is NULL
bool stack_is_full(Stack* s);       // Return false if S is NULL
bool stack_push(Stack* stack, SDATA_TYPE value); // Return false on any failure:
bool stack_pop(Stack* stack, SDATA_TYPE* value); // Return false on any failure:
bool stack_peek(Stack* stack, SDATA_TYPE* value); // Return false on any failure:
void stack_free(Stack* s);

#endif // STACK_H
