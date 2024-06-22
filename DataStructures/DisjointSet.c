#include "DisjointSet.h"
#include <stdlib.h>

DisjointSet* disjoint_set_create(DS_DATA_TYPE size) {
    DisjointSet* ds = (DisjointSet*)malloc(sizeof(DisjointSet));
    if (!ds) return NULL;

    ds->parent = (DS_DATA_TYPE*)malloc(size * sizeof(DS_DATA_TYPE));
    ds->rank = (DS_DATA_TYPE*)malloc(size * sizeof(DS_DATA_TYPE));
    if (!ds->parent || !ds->rank) {
        free(ds->parent);
        free(ds->rank);
        free(ds);
        return NULL;
    }

    ds->size = size;
    for (DS_DATA_TYPE i = 0; i < size; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }

    return ds;
}

void disjoint_set_free(DisjointSet* ds) {
    if (!ds) return;

    free(ds->parent);
    free(ds->rank);
    free(ds);
}

DS_DATA_TYPE disjoint_set_find(DisjointSet* ds, DS_DATA_TYPE element) {
    if (ds->parent[element] != element)
        ds->parent[element] = disjoint_set_find(ds, ds->parent[element]);
    return ds->parent[element];
}

bool disjoint_set_union(DisjointSet* ds, DS_DATA_TYPE x, DS_DATA_TYPE y) {
    DS_DATA_TYPE xRoot = disjoint_set_find(ds, x);
    DS_DATA_TYPE yRoot = disjoint_set_find(ds, y);

    if (xRoot == yRoot) return false;

    if (ds->rank[xRoot] < ds->rank[yRoot]) {
        ds->parent[xRoot] = yRoot;
    }
    else if (ds->rank[xRoot] > ds->rank[yRoot]) {
        ds->parent[yRoot] = xRoot;
    }
    else {
        ds->parent[yRoot] = xRoot;
        ds->rank[xRoot] = ds->rank[xRoot] + 1;
    }

    return true;
}
