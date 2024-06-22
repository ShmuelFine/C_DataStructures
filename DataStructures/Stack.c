#include "Stack.h"
#include <stdlib.h>

Stack* stack_create(int capacity) {
	if (capacity <= 0) return NULL;

	Stack* stack = malloc(sizeof(Stack));
	if (!stack) return NULL;

	stack->data = malloc(capacity * sizeof(SDATA_TYPE));
	if (!stack->data) {
		free(stack);
		return NULL;
	}

	stack->capacity = capacity;
	stack->top = -1;
	return stack;
}

int stack_get_capacity(Stack* s)	{ return s ? s->capacity : -1; }
int stack_get_size(Stack* s)		{ return s ? s->top + 1 : -1; }
bool stack_is_empty(Stack* s)		{ return s && s->top == -1; }
bool stack_is_full(Stack* s)		{ return s && s->top == s->capacity - 1; }

bool stack_push(Stack* stack, SDATA_TYPE value) {
	if (stack_is_full(stack)) return false;

	stack->data[++stack->top] = value;
	return true;
}

bool stack_pop(Stack* stack, SDATA_TYPE* value) {
	if (stack_is_empty(stack) || !value) return false;

	*value = stack->data[stack->top--];
	return true;
}

bool stack_peek(Stack* stack, SDATA_TYPE* value) {
	if (stack_is_empty(stack) || !value) return false;

	*value = stack->data[stack->top];
	return true;
}

void stack_free(Stack* s) {
	if (s->data) free(s->data);
	if (s) free(s);
}
