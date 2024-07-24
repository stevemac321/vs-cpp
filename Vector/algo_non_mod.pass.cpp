/*==============================================================================
 Name        : algo_non_mod.pass.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#pragma once
#include "common.h"

/// Testing with std::pairs and strings
///
void anmp_test1()
{
	TC_BEGIN(__func__);
	vector<std::pair<int, std::string>> v1;
	v1.push_back(std::make_pair(1, "one"));
	v1.push_back(std::make_pair(2, "two"));
	v1.push_back(std::make_pair(3, "three"));
	auto it = std::find_if(
	    v1.begin(), v1.end(),
	    [](const std::pair<int, std::string> &i) { return i.first == 3; });

	int res = (*it).first;
	VERIFY(res == 3);
}
/// might be a redundant test...
///
void anmp_test2()
{
	TC_BEGIN(__func__);
	vector<int> v{0, 1, 2, 3, 4, 5};
	auto v2 = v;
	bool res = std::equal(v.begin(), v.end(), v.begin());
	VERIFY(res == true);
}
/// std::accumulate non-modifying
///
void anmp_test3()
{
	TC_BEGIN(__func__);
	vector<int> v = {1, 2, 3, 4};
	int res = std::accumulate(v.begin(), v.end(), 0);
	VERIFY(res == 10);
	PASSED(__func__, __LINE__);
}


int algo_non_mod_pass()
{
	anmp_test1();
	anmp_test2();
	anmp_test3();
	return failed;
}
