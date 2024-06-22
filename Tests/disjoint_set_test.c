#include "DisjointSet.h"
#include "disjoint_set_test.h"

TEST_FUN_IMPL(DisjointSetTest, CreateAndFind) {
    DisjointSet* ds = disjoint_set_create(10);
    TEST_ASSERT(ds != NULL);

    for (DS_DATA_TYPE i = 0; i < 10; i++) {
        TEST_ASSERT_EQ(disjoint_set_find(ds, i), i, "%d");
    }

    disjoint_set_free(ds);
} END_FUN

TEST_FUN_IMPL(DisjointSetTest, UnionAndFind) {
    DisjointSet* ds = disjoint_set_create(10);

    disjoint_set_union(ds, 0, 1);
    disjoint_set_union(ds, 1, 2);
    disjoint_set_union(ds, 3, 4);

    TEST_ASSERT_EQ(disjoint_set_find(ds, 0), disjoint_set_find(ds, 2), "%d");
    TEST_ASSERT_EQ(disjoint_set_find(ds, 3), disjoint_set_find(ds, 4), "%d");
    TEST_ASSERT_NE(disjoint_set_find(ds, 0), disjoint_set_find(ds, 3), "%d");

    disjoint_set_free(ds);
} END_FUN

INIT_TEST_SUITE(DisjointSetTest)
BIND_TEST(DisjointSetTest, CreateAndFind)
BIND_TEST(DisjointSetTest, UnionAndFind)
END_INIT_TEST_SUITE(DisjointSetTest)
