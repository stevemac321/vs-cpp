#pragma once
#include <algorithm>
#include <cassert>
#include <cstdbool>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <exception>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <limits>
#include <stdarg.h>
#include <string>
#include <type_traits>
#include <utility>
#include <queue>
#include "allocator.hpp"
#include "iterator.hpp"
#include "vector.hpp"

using namespace stevemac;

void STEVEMAC_TRACE(const char* fmt, ...);

/// returns the size of a (statically available) raw array of T
template <typename T, size_t N> constexpr size_t array_size(T(&)[N])
{
	return N;
}

template <typename T> void dump(const vector<T>& v)
{

	printf("capacity: %d size: %d\n", v.capacity(), v.size());

}
template <typename T> void dump(vector<T>& v, const char* msg)
{
	printf("%s\n", msg);
	dump(v);
}
template <typename T>
bool validate_cap(const vector<T>& v, const typename vector<T>::size_type cap)
{

	if (v.capacity() != cap) {
		STEVEMAC_TRACE("expected cap: %d actual: %d\n", cap, v.capacity());
		return false;
	}
	return true;
}

/// Useful function to check the valid state of a vector after some operation.
/// If a vector can be reversed and sorted, its state can be assumed to be
/// reasonably stable (one would think :-) ).
template <typename T>
bool reverse_sort_compare(vector<T>& v, const vector<T>& compare)
{
	std::reverse(v.begin(), v.end());
	std::sort(v.begin(), v.end());
	return v == compare;
}

template <typename T> void ilpush(vector<T>& v, std::initializer_list<T> il)
{

	for (auto& i : il)
		v.push_back(i);
}
/// REVIEW used for spcializing the Test templates. It provides terseness
/// when writing Test instances.  Open to suggestions...
/// this enum describes the type of operation such as "copy assign"
const bool copy = false;
const bool move = true;
const bool empty = true;
const bool diff = false;

/// Primary template:
template <typename T, bool Move, bool EmptyState> struct Test {
};

/// Specialization: copy construct,both source and destination are empty.
template <typename T> struct Test<T, copy, empty> {

	bool execute(const vector<T>& x, const vector<T>& y)
	{

		if (!validate_cap(x, 0))
			return false;
		if (!validate_cap(y, 0))
			return false;

		return x == y;
	}
};
// copy, at copied from not empty
template <typename T> struct Test<T, copy, diff> {
	bool execute(vector<T> x, vector<T> y)
	{

		if (!reverse_sort_compare(x, x))
			return false;
		if (!reverse_sort_compare(y, y))
			return false;

		return x == y;
	}
};
// move both empty
template <typename T> struct Test<T, move, empty> {

	bool execute(const vector<T>& movedfrom, vector<T>& v)
	{

		if (!validate_cap(v, 0))
			return false;

		return reverse_sort_compare(v, v);
	}
};
//
// move moved from not empty
template <typename T> struct Test<T, move, diff> {

	bool execute(vector<T>& movedfrom, vector<T>& v,
		const typename vector<T>::size_type cap)
	{

		if (!validate_cap(v, cap))
			return false;

		return reverse_sort_compare(v, v);
	}
};


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
