#ifndef __COOP_TESTS__STACK_TEST___H__
#define __COOP_TESTS__STACK_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(StackTest);
ADD_TEST(StackTest, StackCreationAndBasicOperations);
ADD_TEST(StackTest, PushAndPeekOperations);
ADD_TEST(StackTest, PopOperation);
ADD_TEST(StackTest, FullStack);
ADD_TEST(StackTest, EmptyStack);
END_TEST_SUITE(StackTest);

#endif