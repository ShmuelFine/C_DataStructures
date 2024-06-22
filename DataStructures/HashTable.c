#include "HashTable.h"
#include <string.h>

HashTable* HT_Create(size_t size, HashFunction hashFunction) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->hashFunction = hashFunction;
    table->buckets = (HashTableEntry**)malloc(size * sizeof(HashTableEntry*));
    for (size_t i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

void HT_Destroy(HashTable* table) {
    for (size_t i = 0; i < table->size; i++) {
        HashTableEntry* entry = table->buckets[i];
        while (entry != NULL) {
            HashTableEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int HT_Insert(HashTable* table, HASH_TABLE_DATA_TYPE data) {
    size_t index = table->hashFunction(&data, table->size);
    HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry));
    if (!newEntry) return 0; // Allocation failed

    newEntry->data = data;
    newEntry->next = table->buckets[index];
    table->buckets[index] = newEntry;

    return 1; // Success
}

int HT_Search(HashTable* table, HASH_TABLE_DATA_TYPE data) {
    size_t index = table->hashFunction(&data, table->size);
    HashTableEntry* entry = table->buckets[index];
    while (entry != NULL) {
        if (entry->data == data) {
            return 1; // Found
        }
        entry = entry->next;
    }
    return 0; // Not found
}

int HT_Remove(HashTable* table, HASH_TABLE_DATA_TYPE data) {
    size_t index = table->hashFunction(&data, table->size);
    HashTableEntry* entry = table->buckets[index];
    HashTableEntry* prev = NULL;

    while (entry != NULL) {
        if (entry->data == data) {
            if (prev == NULL) {
                table->buckets[index] = entry->next;
            }
            else {
                prev->next = entry->next;
            }
            free(entry);
            return 1; // Success
        }
        prev = entry;
        entry = entry->next;
    }
    return 0; // Not found
}
