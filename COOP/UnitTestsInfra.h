#ifndef __UNIT_TESTS_INFRA__
#define __UNIT_TESTS_INFRA__

#include <stdbool.h>
#include <stdio.h>
#include "UnitTestsInfra.h"
#include "ObjectLifecycleManagement.h"
#include "MathUtils.h"

//////////////////////////////////////////////////////////////
/// in the H file:
#define TESTS_LINKED_LIST_TYPE(SUITE_NAME) __single__test_link ##SUITE_NAME ##_t_

#define DEF_TEST_SUITE(SUITE_NAME)\
DEF_CLASS(SUITE_NAME);\
END_DEF(SUITE_NAME);  \
					  \
FUNCTIONS(SUITE_NAME);\
struct TESTS_LINKED_LIST_TYPE(SUITE_NAME) {								\
	int (*_test_func)(SUITE_NAME* _this, int* __is_fail__);		\
	char* name;												\
	struct TESTS_LINKED_LIST_TYPE(SUITE_NAME)* next;						\
}__tests_anchor;											\
MEM_FUN_DECL(SUITE_NAME, __run_all_tests__, struct TESTS_LINKED_LIST_TYPE(SUITE_NAME)* tests_anchor, int* num_passed, int* num_failed)

#define TEST_LINK_NAME(test_name) __ ##test_name ##__LINK_
#define TESTS_ANCHOR(SUITE_NAME) (SUITE_NAME ##VTable.__tests_anchor)

#define ADD_TEST(SUITE_NAME, TEST_NAME)\
MEM_FUN_DECL(SUITE_NAME, TEST_NAME, int * __is_fail__);\
struct TESTS_LINKED_LIST_TYPE(SUITE_NAME) TEST_LINK_NAME(TEST_NAME)

#define END_TEST_SUITE(SUITE_NAME)\
END_FUNCTIONS(SUITE_NAME);

//////////////////////////////////////////////////////////////
/// in the C file:
#define TEST_FUN_IMPL(SUITE_NAME, test_name)\
MEM_FUN_IMPL(SUITE_NAME, test_name, int* __is_fail__)

extern const char* out_file_path;
extern int __NUM_TESTED_CLASSES__;
extern double __ACCAMULATED_SUITES_GRADE__;

void double_print(const char* const format, ...);
double my_ceil(double num);

#define INIT_TEST_SUITE_WITH_SPECIFIC_MEM_SPACE(SUITE_NAME, memSpaceType, memSpaceSize) \
DEF_CTOR(SUITE_NAME) { init_global_memory(memSpaceSize, memSpaceType); } END_CTOR; \
DEF_DTOR(SUITE_NAME) {} END_DTOR; \
MEM_FUN_IMPL(SUITE_NAME, __run_all_tests__, struct TESTS_LINKED_LIST_TYPE(SUITE_NAME)* tests_anchor, int* num_passed, int* num_failed)\
{\
	__NUM_TESTED_CLASSES__++;\
	double num_tests = 0;\
	for (struct TESTS_LINKED_LIST_TYPE(SUITE_NAME)* it = tests_anchor; it != NULL; it = it->next) { num_tests++;}\
	double gradePerTest = (100. / num_tests);\
	double totalGrade = 0;\
	\
	for (struct TESTS_LINKED_LIST_TYPE(SUITE_NAME)* it = tests_anchor; it != NULL; it = it->next) {\
		int is_fail = false;\
		int __INNER_FUNC_CALL_RET_VALUE__ = it->_test_func(_this, &is_fail);\
		bool is_throw = IN_THROWING_VALUE == __INNER_FUNC_CALL_RET_VALUE__;\
		if (is_throw) { is_fail = true; }\
		\
		double_print( "Comment :=>> %s::%s: %s. %d marks\n" , #SUITE_NAME, it->name, is_fail ? "failure" : "success", is_fail ? 0 : (int)my_ceil(gradePerTest)); \
		if (is_throw) {double_print( "<|-- \n %s \n --|>\n" , LAST_EXCEPTION_ERROR_MSG); } \
		totalGrade += is_fail ? 0 : gradePerTest; \
	}\
	__ACCAMULATED_SUITES_GRADE__ += totalGrade; \
	double_print( "Comment :=>> Grade for suite: %d\n", (int)my_ceil(MIN(totalGrade, 100))); \
}\
END_FUN; \
INIT_CLASS(SUITE_NAME); \
TESTS_ANCHOR(SUITE_NAME).next = NULL; \
BIND(SUITE_NAME, __run_all_tests__);

#define PREPARE_TO_RUN_TESTS() {\
	__NUM_TESTED_CLASSES__ = 0;	\
	__ACCAMULATED_SUITES_GRADE__ = 0;\
	FILE *results_file = fopen(out_file_path, "w"); \
	fclose(results_file); }


#define GIVE_FINAL_GRADE() { \
	__ACCAMULATED_SUITES_GRADE__ = my_ceil(__ACCAMULATED_SUITES_GRADE__ / MAX(1, __NUM_TESTED_CLASSES__)); \
	double_print("Grade :=>> %d\n", (int)MIN(__ACCAMULATED_SUITES_GRADE__, 100.));\
	}


#define INIT_TEST_SUITE(SUITE_NAME)\
INIT_TEST_SUITE_WITH_SPECIFIC_MEM_SPACE(SUITE_NAME, HEAP_BASED_MEMORY, 10)


#define BIND_TEST(SUITE_NAME, test_name)\
BIND(SUITE_NAME, test_name);\
(V_TABLE_INSTANCE(SUITE_NAME).TEST_LINK_NAME(test_name))._test_func = SUITE_NAME ##VTable.test_name.inner_function;\
(V_TABLE_INSTANCE(SUITE_NAME).TEST_LINK_NAME(test_name)).name = #test_name;\
(V_TABLE_INSTANCE(SUITE_NAME).TEST_LINK_NAME(test_name)).next = (SUITE_NAME ##VTable.__tests_anchor).next;\
TESTS_ANCHOR(SUITE_NAME).next = &(SUITE_NAME ##VTable.TEST_LINK_NAME(test_name));

#define END_INIT_TEST_SUITE(SUITE_NAME)\
END_INIT_CLASS(SUITE_NAME);\

extern int __NUM_IMPORTED_CLASSES__;
#define IMPORT_TESTS(SUITE_NAME)\
FUN_IMPL(__run__all__tests ##SUITE_NAME)\
{\
	CREATE(SUITE_NAME, suite) CALL;\
	int num_passed = 0, num_failed = 0;\
	struct TESTS_LINKED_LIST_TYPE(SUITE_NAME)* anchor = TESTS_ANCHOR(SUITE_NAME).next;\
	MFUN(&suite, __run_all_tests__), anchor, & num_passed, & num_failed CALL;\
}END_FUN


#define RUN_TESTS(SUITE_NAME) __run__all__tests ##SUITE_NAME();

#define TEST_ASSERT(x) if (!(x)) {*__is_fail__ = true; THROW_MSG(#x);}
// backward compatibility:
#define NTEST_ASSERT(x) TEST_ASSERT(x)

#define MAX_ASSERT_ERR_MSG_SIZE 1000
char __ASSERT_ERROR_MSG___[MAX_ASSERT_ERR_MSG_SIZE];

#define TEST_ASSERT_OP(x,y, print_format, op, op_name) if (!((x) op (y))) {*__is_fail__ = true; \
memset(__ASSERT_ERROR_MSG___, 0, MAX_ASSERT_ERR_MSG_SIZE);\
sprintf(__ASSERT_ERROR_MSG___, #x " (=" print_format ") is not " op_name #y " (=" print_format ")", (x), (y));\
__ASSERT_ERROR_MSG___[MAX_ASSERT_ERR_MSG_SIZE-1] = 0;\
THROW_MSG(__ASSERT_ERROR_MSG___);\
}


#define TEST_ASSERT_EQ(x,y, print_format) TEST_ASSERT_OP(x,y, print_format, ==, "equal to ")
#define TEST_ASSERT_NE(x,y, print_format) TEST_ASSERT_OP(x,y, print_format, !=, "not equal to ")
#define TEST_ASSERT_LT(x,y, print_format) TEST_ASSERT_OP(x,y, print_format, <, "less than ")
#define TEST_ASSERT_LE(x,y, print_format) TEST_ASSERT_OP(x,y, print_format, <=, "less or equal than ")
#define TEST_ASSERT_GT(x,y, print_format) TEST_ASSERT_OP(x,y, print_format, >, "greater than ")


#define TEST_ASSERT_ARR_EQ_GENERIC(x,y,len, print_format, cmp_func) \
for (int i = 0; i < len; ++i) if (!cmp_func(x[i], y[i])) {*__is_fail__ = true; \
memset(__ASSERT_ERROR_MSG___, 0, MAX_ASSERT_ERR_MSG_SIZE);\
sprintf(__ASSERT_ERROR_MSG___, #x "[%d] (=" print_format ") is not equal to " #y "[%d] (=" print_format ")", i, x[i], i, y[i]);\
__ASSERT_ERROR_MSG___[MAX_ASSERT_ERR_MSG_SIZE-1] = 0;\
THROW_MSG(__ASSERT_ERROR_MSG___);\
}

#define _POD_CMP_EQ_OP(x,y) ((x)==(y))
#define TEST_ASSERT_ARR_EQ(x,y,len, print_format) TEST_ASSERT_ARR_EQ_GENERIC(x,y,len, print_format, _POD_CMP_EQ_OP)
#define TEST_ASSERT_STR_EQ(x,y) TEST_ASSERT_ARR_EQ((x),(y), MAX(strlen(x), strlen(y)), "%c");

#define _STR_CMP_EQ_OP(x,y) (strcmp(x,y)==0)
#define TEST_ASSERT_STR_ARR_EQ(x, y, len) TEST_ASSERT_ARR_EQ_GENERIC(x,y,len, "%s", _STR_CMP_EQ_OP)

#define EXPECT_THROW { int __exception_tester__ = 0; if (1) { TRY {

#define ASSERT_THROW __exception_tester__++; } CATCH {} END_TRY; } \
if (__exception_tester__ != 0) {*__is_fail__ = true; THROW_MSG("FAIL: exception was not thrown");} }


#endif