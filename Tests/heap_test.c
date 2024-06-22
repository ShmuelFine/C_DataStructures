#include "Heap.h"
#include "heap_test.h"

TEST_FUN_IMPL(HeapTest, HeapCreationAndBasicOperations) {
    Heap* h = heap_create(10);
    TEST_ASSERT(h != NULL);
    TEST_ASSERT_EQ(heap_peek_min(h, NULL), false, "%d"); // Should fail because heap is empty
    heap_free(h);
} END_FUN

TEST_FUN_IMPL(HeapTest, InsertAndPeekMin) {
    Heap* h = heap_create(10);
    heap_insert(h, 5);
    heap_insert(h, 3);

    HDATA_TYPE min;
    TEST_ASSERT(heap_peek_min(h, &min));
    TEST_ASSERT_EQ(min, 3, "%d");
    heap_free(h);
} END_FUN

TEST_FUN_IMPL(HeapTest, InsertAndExtractMin) {
    Heap* h = heap_create(10);
    heap_insert(h, 5);
    heap_insert(h, 3);
    heap_insert(h, 8);

    HDATA_TYPE extracted;
    TEST_ASSERT(heap_extract_min(h, &extracted));
    TEST_ASSERT_EQ(extracted, 3, "%d");
    TEST_ASSERT(heap_extract_min(h, &extracted));
    TEST_ASSERT_EQ(extracted, 5, "%d");
    TEST_ASSERT(heap_extract_min(h, &extracted));
    TEST_ASSERT_EQ(extracted, 8, "%d");
    TEST_ASSERT_EQ(heap_extract_min(h, &extracted), false, "%d"); // Heap should be empty now
    heap_free(h);
} END_FUN

TEST_FUN_IMPL(HeapTest, FullHeap) {
    Heap* h = heap_create(2);
    heap_insert(h, 5);
    heap_insert(h, 3);

    // Heap is full now; next insert should fail
    TEST_ASSERT_EQ(heap_insert(h, 7), false, "%d");
    heap_free(h);
} END_FUN

INIT_TEST_SUITE(HeapTest)
BIND_TEST(HeapTest, HeapCreationAndBasicOperations)
BIND_TEST(HeapTest, InsertAndPeekMin)
BIND_TEST(HeapTest, InsertAndExtractMin)
BIND_TEST(HeapTest, FullHeap)
END_INIT_TEST_SUITE(HeapTest)
