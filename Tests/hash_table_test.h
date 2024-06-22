#ifndef __COOP_TESTS__STACK_TEST___H__
#define __COOP_TESTS__HASH_TABLE_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(HashTableTest);
ADD_TEST(HashTableTest, CreateAndDestroy);
ADD_TEST(HashTableTest, InsertAndSearch);
ADD_TEST(HashTableTest, Remove);
END_TEST_SUITE(HashTableTest);

#endif