#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>

#define THREAD_TYPE HANDLE
#define TEST_THREAD_FUNC(func_name, param) DWORD WINAPI func_name(LPVOID param)

void sleep_ms(int milliseconds) { Sleep(milliseconds); }

#define START_TIMER						\
LARGE_INTEGER frequency, start, end;	\
QueryPerformanceFrequency(&frequency);	\
QueryPerformanceCounter(&start);		

#define STOP_TIMER(executionTime)   \
QueryPerformanceCounter(&end);      \
executionTime = (end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

#define START_THREAD(thread_var, thread_func, thread_param)\
thread_var = CreateThread(NULL, 0, thread_func, &thread_param, 0, NULL);

#define THREAD_WAIT(thread_var) \
WaitForSingleObject(thread_var, INFINITE);

#else
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define THREAD_TYPE pthread_t
#define TEST_THREAD_FUNC(func_name, param) void* func_name(void* param)

void sleep_ms(int milliseconds) { usleep(milliseconds * 1000); }


#define START_TIMER						\
struct timespec start, end;				\
clock_gettime(CLOCK_MONOTONIC, &start);

#define STOP_TIMER(executionTime) \
clock_gettime(CLOCK_MONOTONIC, &end); \
executionTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

#define START_THREAD(thread_var, thread_func, thread_param)\
pthread_create(&thread_var, NULL, thread_func, &thread_param);

#define THREAD_WAIT(thread_var) \
pthread_join(thread_var, NULL);

#endif

#define WRAP_AS_THREAD(func_name) \
TEST_THREAD_FUNC(func_name ##__thread, param) { \
	double * threadExecTime = (double*)param;   \
                                                \
	START_TIMER;                                \
                                                \
	func_name();                                \
                                                \
	STOP_TIMER(*threadExecTime);                \
                                                \
	return 0;                                   \
}

#define COMPARE_PERF(Fa, Fb, delta)             \
{                                               \
    THREAD_TYPE threads[2];                     \
    double executionTimes[2];                   \
    START_THREAD(threads[0], Fa ##__thread, executionTimes[0]); \
    START_THREAD(threads[1], Fb ##__thread, executionTimes[1]); \
                                                \
    for (int i = 0; i < 2; i++) {               \
        THREAD_WAIT(threads[i]);                \
    }                                           \
    delta = executionTimes[1] - executionTimes[0]; \
}
