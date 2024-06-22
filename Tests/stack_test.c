#include "Stack.h"
#include "stack_test.h"

TEST_FUN_IMPL(StackTest, StackCreationAndBasicOperations) {
    Stack* s = stack_create(10);
    TEST_ASSERT(s != NULL);
    TEST_ASSERT_EQ(stack_get_capacity(s), 10, "%d");
    TEST_ASSERT_EQ(stack_get_size(s), 0, "%d");
    TEST_ASSERT(stack_is_empty(s));
    TEST_ASSERT(!stack_is_full(s));
    stack_free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, PushAndPeekOperations) {
    Stack* s = stack_create(2);
    bool pushResult = stack_push(s, 'A');
    TEST_ASSERT(pushResult);
    TEST_ASSERT_EQ(stack_get_size(s), 1, "%d");

    SDATA_TYPE top;
    bool peekResult = stack_peek(s, &top);
    TEST_ASSERT(peekResult);
    TEST_ASSERT_EQ(top, 'A', "%c");
    stack_free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, PopOperation) {
    Stack* s = stack_create(2);
    stack_push(s, 'A');
    stack_push(s, 'B');

    SDATA_TYPE popped;
    bool popResult = stack_pop(s, &popped);
    TEST_ASSERT(popResult);
    TEST_ASSERT_EQ(popped, 'B', "%c");
    TEST_ASSERT_EQ(stack_get_size(s), 1, "%d");
    stack_free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, FullStack) {
    Stack* s = stack_create(1);
    stack_push(s, 'A');
    TEST_ASSERT(stack_is_full(s));
    TEST_ASSERT(!stack_push(s, 'B')); // Should not be able to push on full stack
    stack_free(s);
} END_FUN

TEST_FUN_IMPL(StackTest, EmptyStack) {
    Stack* s = stack_create(1);
    TEST_ASSERT(stack_is_empty(s));

    SDATA_TYPE popped;
    TEST_ASSERT(!stack_pop(s, &popped)); // Should not pop from an empty stack
    stack_free(s);
} END_FUN

INIT_TEST_SUITE(StackTest)
BIND_TEST(StackTest, StackCreationAndBasicOperations)
BIND_TEST(StackTest, PushAndPeekOperations)
BIND_TEST(StackTest, PopOperation)
BIND_TEST(StackTest, FullStack)
BIND_TEST(StackTest, EmptyStack)
END_INIT_TEST_SUITE(StackTest)
