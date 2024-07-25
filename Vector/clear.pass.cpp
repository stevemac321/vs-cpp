/*==============================================================================
 Name        : clear.pass.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#pragma once
#include "common.h"

/// initializer_list constructed, then clear.
void cp_test1()
{
	TC_BEGIN(__func__);
	vector<int> v{0, 1, 2, 3, 4};
	v.clear();
	VERIFY(v.size() == 0);
}
/// size_type n constructed then cleared.
void cp_test2()
{
	TC_BEGIN(__func__);
	vector<int> v(500);
	v.clear();
	VERIFY(v.size() == 0);
}
/// size_type n constructed, cleared, then re-initialized with
// initializer_list; then std::reverse, std::copy, std::equal.
void cp_test3()
{
	TC_BEGIN(__func__);
	vector<int> v(500);
	v.clear();
	v = vector<int>({0, 1, 2, 3, 4});
	VERIFY(v.size() == 5);
	VERIFY(v.capacity() == 5);
	VERIFY(reverse_sort_compare(v, v));
}

int clear_pass()
{
	cp_test1();
	cp_test2();
	cp_test3();
	return failed;
}
