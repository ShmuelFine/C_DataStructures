#ifndef __COOP_TESTS__QUEUE_TEST___H__
#define __COOP_TESTS__QUEUE_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(QueueTest);
ADD_TEST(QueueTest, QueueCreationAndBasicOperations);
ADD_TEST(QueueTest, EnqueueAndPeekOperations);
ADD_TEST(QueueTest, DequeueOperation);
ADD_TEST(QueueTest, FullQueue);
END_TEST_SUITE(QueueTest);

#endif