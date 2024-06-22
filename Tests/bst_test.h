#ifndef __COOP_TESTS__BST_TEST___H__
#define __COOP_TESTS__BST_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(BSTTest);
ADD_TEST(BSTTest, CreateAndInsert);
ADD_TEST(BSTTest, FindNonExistent);
END_TEST_SUITE(BSTTest);

#endif