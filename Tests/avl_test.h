#ifndef __COOP_TESTS__AVL_TEST___H__
#define __COOP_TESTS__AVL_TEST___H__

#include "UnitTestsInfra.h"
#include "COOP.h"

DEF_TEST_SUITE(AVLTreeTest);
ADD_TEST(AVLTreeTest, ValidAVLTreeInitialization);
ADD_TEST(AVLTreeTest, AVLTreeInsert);
ADD_TEST(AVLTreeTest, AVLTreeInsertAndDelete);
ADD_TEST(AVLTreeTest, AVLTreeInsertDeleteAndCheck);
ADD_TEST(AVLTreeTest, LargeInsertHeightCheck);
//
//ADD_TEST(AVLTreeTest, CreateAndDestroy);
//ADD_TEST(AVLTreeTest, InsertAndSearch);
//ADD_TEST(AVLTreeTest, Remove);
//ADD_TEST(AVLTreeTest, BalanceCheck);
//ADD_TEST(AVLTreeTest, LargeInsertHeightCheck);
END_TEST_SUITE(AVLTreeTest);

#endif