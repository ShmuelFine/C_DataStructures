#include "UnitTestsInfra.h"

#include "avl_test.h"
#include "bst_test.h"
#include "disjoint_set_test.h"
#include "hash_table_test.h"
#include "heap_test.h"
#include "queue_test.h"
#include "stack_test.h"
#include "vector_test.h"


IMPORT_TESTS(AVLTreeTest);
IMPORT_TESTS(BSTTest);
IMPORT_TESTS(DisjointSetTest);
IMPORT_TESTS(HashTableTest);
IMPORT_TESTS(HeapTest);
IMPORT_TESTS(QueueTest);
IMPORT_TESTS(StackTest);
IMPORT_TESTS(VectorTest);


int main() {

	init_global_memory(0, HEAP_BASED_MEMORY);
	PREPARE_TO_RUN_TESTS();
	RUN_TESTS(AVLTreeTest);
	RUN_TESTS(BSTTest);
	RUN_TESTS(DisjointSetTest);
	RUN_TESTS(HashTableTest);
	RUN_TESTS(HeapTest);
	RUN_TESTS(QueueTest);
	RUN_TESTS(StackTest);
	RUN_TESTS(VectorTest);

	GIVE_FINAL_GRADE();

	return 0;

}

