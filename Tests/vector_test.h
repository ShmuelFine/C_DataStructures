#ifndef __COOP_TESTS__VECTOR_TEST___H__
#define __COOP_TESTS__VECTOR_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(VectorTest);
ADD_TEST(VectorTest, CreateAndDestroy);
ADD_TEST(VectorTest, InsertAndAccess);
ADD_TEST(VectorTest, CapacityIncrease);
ADD_TEST(VectorTest, LargeInsertCheck);
END_TEST_SUITE(VectorTest);

#endif