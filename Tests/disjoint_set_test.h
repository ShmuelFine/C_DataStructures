#ifndef __COOP_TESTS__DSU_TEST___H__
#define __COOP_TESTS__DSU_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(DisjointSetTest);
ADD_TEST(DisjointSetTest, CreateAndFind);
ADD_TEST(DisjointSetTest, UnionAndFind);
END_TEST_SUITE(DisjointSetTest);

#endif