
#pragma once
enum insert_state { INSERTED, EXISTS, TABLEFULL };
typedef struct open_table open_table;
typedef open_table* tableptr;
typedef void* genptr;

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "heap.h"
#include "open_table.h"
#include "algo.h"
#include "functor.h"

/* array size macros */
#ifndef _countof
#define _countof(x) sizeof(x) / sizeof(x[0])
#endif

#ifndef _gridcountof
#define _gridcountof(x) sizeof(x) / sizeof(x[0][0])
#endif

/* TEST HARNESS*/
extern int passed;
extern int failed;
extern int tcs;
#define TC_BEGIN(func) \
	printf("--------------------TESTCASE BEGIN %s ---------------------\n", func); \
	tcs++;
#define VERIFY(x) \
	(x) ? passed++ : failed++; \
	assert(x)
#define PASSED(func, line) \
	printf("--------------------PASSED %s Line: %d --------------------\n", func, line); \
	passed++;
#define REPORT(msg) \
	printf("--%s TESTCASES: %d TESTS PASSED: %d TESTS FAILED: %d-------\n", msg, tcs, passed, failed);

