#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define QDATA_TYPE char

typedef struct {
    QDATA_TYPE* data;
    int capacity;
    int front;
    int rear;
    int size;
} Queue;

Queue* queue_create(int capacity);
int queue_get_capacity(Queue* q);
int queue_get_size(Queue* q);
bool queue_is_empty(Queue* q);
bool queue_is_full(Queue* q);
bool queue_enqueue(Queue* q, QDATA_TYPE value);
bool queue_dequeue(Queue* q, QDATA_TYPE* value);
bool queue_peek(Queue* q, QDATA_TYPE* value); // returns value of "front" of the queue.
void queue_free(Queue* q);

#endif // QUEUE_H
