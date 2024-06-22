#include "Heap.h"
#include <stdlib.h>

Heap* heap_create(int capacity) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    if (!h) return NULL;

    h->data = (HDATA_TYPE*)malloc(capacity * sizeof(HDATA_TYPE));
    if (!h->data) {
        free(h);
        return NULL;
    }

    h->capacity = capacity;
    h->size = 0;
    return h;
}

void heap_free(Heap* h) {
    if (h) {
        free(h->data);
        free(h);
    }
}

void swap(HDATA_TYPE* a, HDATA_TYPE* b) {
    HDATA_TYPE temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap* h, int index) {
    while (index != 0 && h->data[(index - 1) / 2] > h->data[index]) {
        swap(&h->data[(index - 1) / 2], &h->data[index]);
        index = (index - 1) / 2;
    }
}

bool heap_insert(Heap* h, HDATA_TYPE value) {
    if (h->size == h->capacity) return false;

    h->data[h->size] = value;
    heapify_up(h, h->size);
    h->size++;
    return true;
}

void heapify_down(Heap* h, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < h->size && h->data[leftChild] < h->data[smallest])
        smallest = leftChild;

    if (rightChild < h->size && h->data[rightChild] < h->data[smallest])
        smallest = rightChild;

    if (smallest != index) {
        swap(&h->data[index], &h->data[smallest]);
        heapify_down(h, smallest);
    }
}

bool heap_extract_min(Heap* h, HDATA_TYPE* value) {
    if (h->size == 0) return false;

    *value = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapify_down(h, 0);
    return true;
}

bool heap_peek_min(Heap* h, HDATA_TYPE* value) {
    if (h->size == 0) return false;

    *value = h->data[0];
    return true;
}
