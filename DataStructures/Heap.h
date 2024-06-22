#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

#define HDATA_TYPE int

typedef struct {
    HDATA_TYPE* data;
    int capacity;
    int size;
} Heap;

Heap* heap_create(int capacity);
void heap_free(Heap* h);

bool heap_insert(Heap* h, HDATA_TYPE value);
bool heap_extract_min(Heap* h, HDATA_TYPE* value);
bool heap_peek_min(Heap* h, HDATA_TYPE* value);

#endif // HEAP_H
