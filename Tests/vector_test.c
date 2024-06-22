#include "Vector.h"
#include "vector_test.h"

TEST_FUN_IMPL(VectorTest, CreateAndDestroy) {
    // Arrange
    Vector* vec = Vec_Create(10);

    // Assert
    TEST_ASSERT(vec != NULL);
    TEST_ASSERT(vec->size == 0);
    TEST_ASSERT(vec->capacity == 10);

    // Cleanup
    Vec_Destroy(vec);
} END_FUN

TEST_FUN_IMPL(VectorTest, InsertAndAccess) {
    // Arrange
    Vector* vec = Vec_Create(2);
    int data1 = 42, data2 = 21, data3 = 63;

    // Act
    int insertResult1 = Vec_Insert(vec, data1);
    int insertResult2 = Vec_Insert(vec, data2);
    int insertResult3 = Vec_Insert(vec, data3);

    // Assert
    TEST_ASSERT(insertResult1 == 1);
    TEST_ASSERT(insertResult2 == 1);
    TEST_ASSERT(insertResult3 == 1);
    TEST_ASSERT(Vec_At(vec, 0) == data1);
    TEST_ASSERT(Vec_At(vec, 1) == data2);
    TEST_ASSERT(Vec_At(vec, 2) == data3);
    TEST_ASSERT(Vec_Size(vec) == 3);
    TEST_ASSERT(Vec_Capacity(vec) >= 3);

    // Cleanup
    Vec_Destroy(vec);
} END_FUN

TEST_FUN_IMPL(VectorTest, CapacityIncrease) {
    // Arrange
    Vector* vec = Vec_Create(2);

    // Act
    for (int i = 0; i < 3; i++) {
        Vec_Insert(vec, i);
    }

    // Assert
    TEST_ASSERT(Vec_Size(vec) == 3);
    TEST_ASSERT(Vec_Capacity(vec) >= 3);

    // Cleanup
    Vec_Destroy(vec);
} END_FUN

TEST_FUN_IMPL(VectorTest, LargeInsertCheck) {
    // Arrange
    Vector* vec = Vec_Create(2);
    int numElements = 1000;

    // Act
    for (int i = 0; i < numElements; i++) {
        Vec_Insert(vec, i);
    }

    // Assert
    TEST_ASSERT(Vec_Size(vec) == numElements);
    TEST_ASSERT(Vec_Capacity(vec) >= numElements);

    for (int i = 0; i < numElements; i++) {
        TEST_ASSERT(Vec_At(vec, i) == i);
    }

    // Cleanup
    Vec_Destroy(vec);
} END_FUN

INIT_TEST_SUITE(VectorTest)
BIND_TEST(VectorTest, CreateAndDestroy)
BIND_TEST(VectorTest, InsertAndAccess)
BIND_TEST(VectorTest, CapacityIncrease)
BIND_TEST(VectorTest, LargeInsertCheck)
END_INIT_TEST_SUITE(VectorTest)
