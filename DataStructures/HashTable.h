#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

#define HASH_TABLE_DATA_TYPE int

typedef struct HashTableEntry {
    HASH_TABLE_DATA_TYPE data;
    struct HashTableEntry* next;
} HashTableEntry;

typedef size_t(*HashFunction)(HASH_TABLE_DATA_TYPE* data, size_t size);

typedef struct {
    HashTableEntry** buckets;
    size_t size;
    HashFunction hashFunction;
} HashTable;

HashTable* HT_Create(size_t size, HashFunction hashFunction);
void HT_Destroy(HashTable* table);
int HT_Insert(HashTable* table, HASH_TABLE_DATA_TYPE data);
int HT_Search(HashTable* table, HASH_TABLE_DATA_TYPE data);
int HT_Remove(HashTable* table, HASH_TABLE_DATA_TYPE data);

#endif // HASHTABLE_H
