#ifndef __COOP_TESTS__HEAP_TEST___H__
#define __COOP_TESTS__HEAP_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(HeapTest);
ADD_TEST(HeapTest, HeapCreationAndBasicOperations);
ADD_TEST(HeapTest, InsertAndPeekMin);
ADD_TEST(HeapTest, InsertAndExtractMin);
ADD_TEST(HeapTest, FullHeap);
END_TEST_SUITE(HeapTest);

#endif