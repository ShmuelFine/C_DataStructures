#include "Vector.h"
#include <stdlib.h>
#include <string.h>

Vector* Vec_Create(size_t initialCapacity) {
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->data = (VECTOR_DATA_TYPE*)malloc(initialCapacity * sizeof(VECTOR_DATA_TYPE));
    vec->size = 0;
    vec->capacity = initialCapacity;
    return vec;
}

void Vec_Destroy(Vector* vec) {
    free(vec->data);
    free(vec);
}

static void Vec_Resize(Vector* vec, size_t newCapacity) {
    VECTOR_DATA_TYPE* newData = (VECTOR_DATA_TYPE*)realloc(vec->data, newCapacity * sizeof(VECTOR_DATA_TYPE));
    if (newData) {
        vec->data = newData;
        vec->capacity = newCapacity;
    }
}

int Vec_Insert(Vector* vec, VECTOR_DATA_TYPE val) {
    if (vec->size == vec->capacity) {
        Vec_Resize(vec, vec->capacity * 2);
    }
    vec->data[vec->size++] = val;
    return 1;
}

VECTOR_DATA_TYPE Vec_At(Vector* vec, int idx) {
    if (idx >= 0 && idx < vec->size) {
        return vec->data[idx];
    }
    // Handle error case as you prefer, here we return 0 as an example
    return 0;
}

size_t Vec_Size(Vector* vec) {
    return vec->size;
}

size_t Vec_Capacity(Vector* vec) {
    return vec->capacity;
}
