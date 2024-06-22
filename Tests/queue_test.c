#include "Queue.h"
#include "queue_test.h"

TEST_FUN_IMPL(QueueTest, QueueCreationAndBasicOperations) {
    Queue* q = queue_create(10);
    TEST_ASSERT(q != NULL);
    TEST_ASSERT_EQ(queue_get_capacity(q), 10, "%d");
    TEST_ASSERT_EQ(queue_get_size(q), 0, "%d");
    TEST_ASSERT(queue_is_empty(q));
    TEST_ASSERT(!queue_is_full(q));
    queue_free(q);
} END_FUN

TEST_FUN_IMPL(QueueTest, EnqueueAndPeekOperations) {
    Queue* q = queue_create(2);
    bool enqueueResult = queue_enqueue(q, 'A');
    TEST_ASSERT(enqueueResult);
    TEST_ASSERT_EQ(queue_get_size(q), 1, "%d");

    QDATA_TYPE front;
    bool peekResult = queue_peek(q, &front);
    TEST_ASSERT(peekResult);
    TEST_ASSERT_EQ(front, 'A', "%c");
    queue_free(q);
} END_FUN

TEST_FUN_IMPL(QueueTest, DequeueOperation) {
    Queue* q = queue_create(2);
    queue_enqueue(q, 'A');
    queue_enqueue(q, 'B');

    QDATA_TYPE dequeued;
    bool dequeueResult = queue_dequeue(q, &dequeued);
    TEST_ASSERT(dequeueResult);
    TEST_ASSERT_EQ(dequeued, 'A', "%c");
    TEST_ASSERT_EQ(queue_get_size(q), 1, "%d");
    queue_free(q);
} END_FUN

TEST_FUN_IMPL(QueueTest, FullQueue) {
    Queue* q = queue_create(1);
    queue_enqueue(q, 'A');
    TEST_ASSERT(queue_is_full(q));
    TEST_ASSERT(!queue_enqueue(q, 'B')); // Should not be able to enqueue on full queue
    queue_free(q);
} END_FUN

INIT_TEST_SUITE(QueueTest)
BIND_TEST(QueueTest, QueueCreationAndBasicOperations)
BIND_TEST(QueueTest, EnqueueAndPeekOperations)
BIND_TEST(QueueTest, DequeueOperation)
BIND_TEST(QueueTest, FullQueue)
END_INIT_TEST_SUITE(QueueTest)

