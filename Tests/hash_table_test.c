#include "HashTable.h"
#include "hash_table_test.h"

size_t defaultHashFunction(HASH_TABLE_DATA_TYPE* data, size_t size) {
    return *data % size;
}

TEST_FUN_IMPL(HashTableTest, CreateAndDestroy) {
    // Arrange
    HashTable* table = HT_Create(10, defaultHashFunction);

    // Assert
    TEST_ASSERT(table != NULL);
    TEST_ASSERT(table->size == 10);
    TEST_ASSERT(table->buckets != NULL);

    // Cleanup
    HT_Destroy(table);
} END_FUN

TEST_FUN_IMPL(HashTableTest, InsertAndSearch) {
    // Arrange
    HashTable* table = HT_Create(10, defaultHashFunction);
    int data = 42;

    // Act
    int insertResult = HT_Insert(table, data);

    // Assert
    TEST_ASSERT(insertResult == 1);
    TEST_ASSERT(HT_Search(table, data) == 1);

    // Cleanup
    HT_Destroy(table);
} END_FUN

TEST_FUN_IMPL(HashTableTest, Remove) {
    // Arrange
    HashTable* table = HT_Create(10, defaultHashFunction);
    int data = 42;
    HT_Insert(table, data);

    // Act
    int removeResult = HT_Remove(table, data);

    // Assert
    TEST_ASSERT(removeResult == 1);
    TEST_ASSERT(HT_Search(table, data) == 0);

    // Cleanup
    HT_Destroy(table);
} END_FUN

INIT_TEST_SUITE(HashTableTest)
BIND_TEST(HashTableTest, CreateAndDestroy)
BIND_TEST(HashTableTest, InsertAndSearch)
BIND_TEST(HashTableTest, Remove)
END_INIT_TEST_SUITE(HashTableTest)
