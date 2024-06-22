#include "Queue.h"
#include <stdlib.h>

Queue* queue_create(int capacity) {
    if (capacity <= 0) return NULL;

    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) return NULL;

    q->data = (QDATA_TYPE*)malloc(capacity * sizeof(QDATA_TYPE));
    if (!q->data) {
        free(q);
        return NULL;
    }

    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

int queue_get_capacity(Queue* q) {
    return q ? q->capacity : -1;
}

int queue_get_size(Queue* q) {
    return q ? q->size : -1;
}

bool queue_is_empty(Queue* q) {
    return q && q->size == 0;
}

bool queue_is_full(Queue* q) {
    return q && q->size == q->capacity;
}

bool queue_enqueue(Queue* q, QDATA_TYPE value) {
    if (queue_is_full(q)) return false;

    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
    return true;
}

bool queue_dequeue(Queue* q, QDATA_TYPE* value) {
    if (queue_is_empty(q) || !value) return false;

    *value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return true;
}

bool queue_peek(Queue* q, QDATA_TYPE* value) {
    if (queue_is_empty(q) || !value) return false;

    *value = q->data[q->front];
    return true;
}

void queue_free(Queue* q) {
    if (!q) return;

    free(q->data);
    free(q);
}
