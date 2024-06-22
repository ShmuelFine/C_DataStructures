#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <stdbool.h>

#define DS_DATA_TYPE int

typedef struct {
    DS_DATA_TYPE* parent;
    int* rank;
    int size;
} DisjointSet;

DisjointSet* disjoint_set_create(int size);
void disjoint_set_free(DisjointSet* ds);

int disjoint_set_find(DisjointSet* ds, DS_DATA_TYPE element);
bool disjoint_set_union(DisjointSet* ds, DS_DATA_TYPE x, DS_DATA_TYPE y);

#endif // DISJOINT_SET_H
