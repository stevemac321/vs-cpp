/*==============================================================================
 Name        : algo_copy_reverse_pass.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/

#include "common.h"
using namespace stevemac;

class Foo
{
      public:
	int x;
	int y;
	float f;
	double d;
	int doit(int x, int y) { return x + y; }
};
/// std::copy, std::equal
void acrp_test1()
{
	TC_BEGIN(__func__);
	vector<int> v1{5, 4, 3, 2, 1};
	vector<int> v2(5);
	std::copy(v1.begin(), v1.end(), v2.begin());
	VERIFY(v1 == v2);

	bool res = std::equal(v1.begin(), v1.end(), v2.begin());
	VERIFY(res == true);
	PASSED(__func__, __LINE__);
	VERIFY(v1 == v2);
}
/// std::reverse, std::equal
///
void acrp_test2()
{
	TC_BEGIN(__func__);
	vector<int> v1 = {0, 1, 2, 3};
	std::reverse(v1.begin(), v1.end());

	vector<int> v2{3, 2, 1, 0};
	bool res = std::equal(v1.begin(), v1.end(), v2.begin());
	VERIFY(res == true);
}
/// std::sort, std::merge
///
void acrp_test3()
{
	TC_BEGIN(__func__);
	vector<int> x{9, 3, 7, 2, 0};
	vector<int> y{8, 1, 5, 6, 4};

	std::sort(x.begin(), x.end());
	std::sort(y.begin(), y.end());

	vector<int> out(10);

	std::merge(x.begin(), x.end(), y.begin(), y.end(), out.begin());
	vector<int> compare{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	VERIFY(out == compare);
}


/// std::swap
///
void acrp_test6()
{
	TC_BEGIN(__func__);
	vector<int> x{0, 1, 2, 3, 4};
	vector<int> y{4, 3, 2, 1, 0};
	std::swap(x, y);
	vector<int> compare_x{4, 3, 2, 1, 0};
	vector<int> compare_y{0, 1, 2, 3, 4};
	VERIFY(x == compare_x);
	VERIFY(y == compare_y);
}
/// std::replace_if
///
void acrp_test7()
{
	TC_BEGIN(__func__);
	vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::replace_if(v.begin(), v.end(), [](int x) { return (x % 2) == 1; },
			55);
	vector<int> compare{0, 55, 2, 55, 4, 55, 6, 55, 8, 55};
	VERIFY(v == compare);
    vector<int> test;
    
}
/// std::unique
///
void acrp_test8()
{
	TC_BEGIN(__func__);
	vector<int> v{0, 0, 1, 1, 2, 2, 3, 3};
	auto ret = std::unique(v.begin(), v.end());
	vector<int> compare{0, 1, 2, 3};
	VERIFY(v == compare);
}
/// main
///
int algo_copy_reverse_pass()
{
	acrp_test1();
	acrp_test2();
	acrp_test3();
	acrp_test6();
	acrp_test7();
	return failed;
}
