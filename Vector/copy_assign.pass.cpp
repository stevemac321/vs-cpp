/*==============================================================================
 Name        : copy_assign.pass.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#pragma once
#include "common.h"

/// Testing the matrix: the template arguments depict the scenario:
/// first parameter is T, second is copy or move, third argument
/// describes the copy\move source, empty or different (full).
/// Note we are testing std::string as T also.
using strpair = std::pair<std::string, std::string>;
int copy_assign_pass()
{
	TC_BEGIN(__func__);
	Test<int, copy, empty> ice;
	VERIFY(ice.execute(vector<int>(), vector<int>()));

	Test<strpair, copy, empty> pce;
	VERIFY(pce.execute(vector<strpair>(), vector<strpair>()));
	Test<int, copy, diff> icd;
	{
		std::initializer_list<int> int5 = {0, 1, 2, 3, 4};
		vector<int> x(int5);
		vector<int> y = x;
		;
		VERIFY(icd.execute(x, y));
	}
	{
		std::initializer_list<int> int9 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		vector<int> x(int9);
		vector<int> y = x;
		VERIFY(icd.execute(x, y));
	}
	{
		std::initializer_list<int> int25 = {
		    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
		    13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
		vector<int> x(int25);
		vector<int> y = x;
		VERIFY(icd.execute(x, y));
	}
	/// push_backed vectors can have larger capacities
	{
		std::initializer_list<int> int5 = {0, 1, 2, 3, 4};
		vector<int> x;
		ilpush(x, int5);
		vector<int> y = x;
		VERIFY(icd.execute(x, y));
	}
	{
		std::initializer_list<int> int9 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		vector<int> x;
		ilpush(x, int9);
		vector<int> y = x;
		VERIFY(icd.execute(x, y));
	}
	{
		vector<int> v(10);
		for (int i = 0; i < 10; i++)
			v[i] = i;

		vector<int> compare{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		VERIFY(v == compare);
	}

	{
		std::initializer_list<int> int25 = {
		    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
		    13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
		vector<int> x;
		ilpush(x, int25);
		vector<int> y = x;
		VERIFY(icd.execute(x, y));
	}

	Test<std::string, copy, diff> scd;

	{
		std::initializer_list<std::string> str5 = {
		    "apple", "berry", "cat", "deer", "eagle"};
		vector<std::string> x(str5);
		vector<std::string> y = x;
		VERIFY(scd.execute(x, y));
	}

	{
		std::initializer_list<std::string> str5 = {
		    "apple", "berry", "cat", "deer", "eagle"};
		vector<std::string> x;
		ilpush(x, str5);
		vector<std::string> y = x;
		VERIFY(scd.execute(x, y));
	}
	return failed;
}
