#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define VECTOR_DATA_TYPE int

typedef struct {
    VECTOR_DATA_TYPE* data;
    size_t size;
    size_t capacity;
} Vector;

Vector* Vec_Create(size_t initialCapacity);
void Vec_Destroy(Vector* vec);
int Vec_Insert(Vector* vec, VECTOR_DATA_TYPE val);
VECTOR_DATA_TYPE Vec_At(Vector* vec, int idx);
size_t Vec_Size(Vector* vec);
size_t Vec_Capacity(Vector* vec);

#endif // VECTOR_H
