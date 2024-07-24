/*==============================================================================
 Name        : main.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include "common.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#define SINE_ARRAY_SIZE 91
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define TABLESIZE 182

#ifndef NL
#define NL printf("\n")
#endif

/* TEST HARNESS*/
int passed = 0;
int failed = 0;
int tcs = 0;
int int_cmp(const int* v1, const int* v2);
void print_int_array(int *arr, const size_t count);
// test functions
void table_test1();
void table_test2();
void sine_table_test();
void print_int_array(int *arr, const size_t count);


void visit_sort_trans_mod_test();
void search_test();
void bit_manip_test();
void merge_test();
void swap_ranges_test();
void random_shuffle_test();
void count_if_test();
void equal_test();
void replace_test();
void reverse_test();
void copy_backward_test();
void product_test();


int main()
{
	Heap_Init();

   table_test1();
   table_test2();
   sine_table_test();
	visit_sort_trans_mod_test();
	search_test();
	merge_test();
	swap_ranges_test();
	random_shuffle_test();
	count_if_test();
	equal_test();
	replace_test();
	reverse_test();
	copy_backward_test();
	product_test();
}
/*-----------------------------------------------------------------------------
Test functions and data
-----------------------------------------------------------------------------*/


void table_test1()
{
	
	TC_BEGIN(__func__);
	tableptr table = open_table_init(TABLESIZE, sizeof(int), inthash, inthash, int_cmp, table_int_alloc);
	VERIFY(table);
	PASSED(__func__, __LINE__);

	int a[97];
	int dupes = 0;
	modify(a, _countof(a), sizeof(int), rand_int);
	print_int_array(a, _countof(a));
	for (int i = 0; i < _countof(a); i++) {
		if (EXISTS == open_table_insert(table, &a[i]))
			dupes++;
	}

	open_table_visit(table, print_int);
	NL;
	
	open_table_cluster_report(table);
	printf("dupes: %d\n", dupes);
	open_table_destroy(table);
	PASSED(__func__, __LINE__);
	
}
void table_test2()
{
	TC_BEGIN(__func__);
	tableptr table = open_table_init(TABLESIZE, sizeof(const char*), strhash, strhash, table_str_cmp, table_str_alloc);
	VERIFY(table);
	PASSED(__func__, __LINE__);
	
	char *a[] = {
    "John", "Mary", "Jane", "Michael", "Sarah", "David", "Laura", "James", "Linda", "Robert",
    "Karen", "Joseph", "Emily", "Charles", "Jennifer", "Thomas", "Jessica", "Daniel", "Megan",
    "Matthew", "Susan", "Brian", "Amanda", "William", "Elizabeth", "Richard", "Melissa",
    "Anthony", "Michelle", "Christopher", "Lisa", "Joshua", "Kimberly", "Andrew", "Sandra",
    "Alexander", "Nancy", "Steven", "Angela", "Edward", "Heather", "Paul", "Rebecca", "Kevin",
    "Laura", "George", "Cynthia", "Jason", "Stephanie", "Timothy", "Sharon", "Mark", "Amy",
    "Jeffrey", "Anna", "Scott", "Donna", "Gary", "Deborah", "Gregory", "Carol", "Kenneth",
    "Ruth", "Ronald", "Katherine", "Patrick"};
	

	size_t len = _countof(a);

	for (int i = 0; i < len; i++)
		open_table_insert(table, a[i]);

	open_table_visit(table, print_str);
	NL;
	char *p = open_table_lookup(table, a[3]);
	if (p)
		printf("found: %s\n", p);

	open_table_remove_entry(table, a[3]);
	open_table_visit(table, print_str);
	NL;

	open_table_cluster_report(table);
	open_table_destroy(table);
	PASSED(__func__, __LINE__);
}
void sine_table_test()
{
	TC_BEGIN(__func__);
	tableptr table = open_table_init(SINE_ARRAY_SIZE * 2, sizeof(int), 
						inthash, inthash, int_cmp, table_int_alloc);
	VERIFY(table);
	
	int compare[SINE_ARRAY_SIZE];
	float sf=0;
	int res=0;
	/* this loop taken from Zhu textbook */
	for(int i=0; i < SINE_ARRAY_SIZE; i++) {
		sf = sin(M_PI * i / 180);
		res = (1 + sf) * 2048;
		if(res == 0x1000)
			res = 0xFFF;
		
		compare[i] = res;
		open_table_insert(table, &res);
	}
	printf("contexts: \n");
	open_table_visit(table, print_hex);
	NL;
	printf("compare: \n");
	for(int i=0; i < SINE_ARRAY_SIZE; i++)
		printf("%X ", compare[i]);
	NL;
	for(int i=0; i < SINE_ARRAY_SIZE; i++) {
		int *p = open_table_lookup(table, &compare[i]);
		VERIFY(p != NULL);
	}
	open_table_cluster_report(table);
	open_table_destroy(table);
}

/*==============================================================================
 Name        : algo tests
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/


// test data
// array interface tests
static int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3};
static int grid[3][3] = {{44, 77, 11}, {2, 100, 77}, {0, 33, 9}};
static const char *strs[] = {"zero", "one", "two", "three", "four"};
static student recs[] = {{"Joe", 2.0},   {"Mary", 4.0},  {"Larry", 3.5},
			 {"Moe", 3.0},   {"Harry", 3.5}, {"Mary", 2.0},
			 {"Jill", 4.0},  {"Jerry", 2.9}, {"Mike", 3.5},
			 {"Harry", 3.0}, {"Abel", 3.5},  {"Abel", 2.0}};

// test helper


/*-----------------------------------------------------------------------------
Test functions and data
-----------------------------------------------------------------------------*/
void visit_sort_trans_mod_test()
{
	TC_BEGIN(__func__);
	gensort(arr, _countof(arr), sizeof(int), int_less, int_swap);
	print_int_array(arr, _countof(arr));
	visit(arr, _countof(arr), sizeof(int), print_int);
	NL;
	transform(arr, arr, _countof(arr), sizeof(int), double_int);
	print_int_array(arr, _countof(arr));
	modify(arr, _countof(arr), sizeof(int), rand_int);
	print_int_array(arr, _countof(arr));
	gensort(arr, _countof(arr), sizeof(int), int_less, int_swap);
	print_int_array(arr, _countof(arr));

	printf("accumulate total: %d\n", accumulate(arr, _countof(arr), sizeof(int),
		       ret_int));
// todo accumulate ints, number of characters, number of words, gpa 	
	
	int test[] = {1,2,3,4,5};
	printf("inner_product: %d\n", inner_product(test, test, _countof(test),
				      sizeof(int), ret_int));
	printf("grid test \n%s\n", __func__);
	gensort(grid, _gridcountof(grid), sizeof(int), int_less, int_swap);
	print_int_array(grid, _gridcountof(grid));

	printf("String sort \n%s\n", __func__);
	gensort(strs, _countof(strs), sizeof(const char *), str_less, str_swap);
	visit(strs, _countof(strs), sizeof(const char *), print_pstr);

	printf("Record struct sort\n%s\n", __func__);
	gensort(recs, _countof(recs), sizeof(student), record_gpaless,
		record_swap);
	visit(recs, _countof(recs), sizeof(student), print_student);
	PASSED(__func__, __LINE__);
}
void search_test()
{
	TC_BEGIN(__func__);
	gensort(arr, _countof(arr), sizeof(int), int_less, int_swap);
	int x = 888;
	VERIFY(NULL == gensearch(arr, &x, 0, _countof(arr)-1, sizeof(int), 
								int_cmp));
	for(int i=0; i < _countof(arr); i++) {
		int val = arr[i];
		int * p = gensearch(arr, &val, 0, _countof(arr)-1, sizeof(int), 
								      int_cmp);
		VERIFY(p && *p == val);
		printf("%d ", *p); 
	}
	NL;
}

void merge_test()
{
	TC_BEGIN(__func__);
	int src1[11] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
	int src2[11] = {91, 81, 71, 61, 51, 41, 31, 21, 11, 1};
	int dest[30];
	deduce_sort(src1, 10);
	deduce_sort(src2, 10);
	print_int_array(src1, 10);
	print_int_array(src2, 10);
	merge(dest, src1, src2, 20, sizeof(int), int_less);
	print_int_array(dest, 20);
	PASSED(__func__, __LINE__);
}
void swap_ranges_test()
{
	TC_BEGIN(__func__);
	int src1[11] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
	int src2[11] = {91, 81, 71, 61, 51, 41, 31, 21, 11, 1};
	print_int_array(src1, _countof(src1));
	print_int_array(src2, _countof(src2));
	swap_ranges(src1, src2, 5, sizeof(int), int_swap);
	print_int_array(src1, _countof(src1));
	print_int_array(src2, _countof(src2));
	PASSED(__func__, __LINE__);
}
void random_shuffle_test()
{
	TC_BEGIN(__func__);
	int a[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
	print_int_array(a, _countof(a));
	deduce_sort(a, _countof(a));
	print_int_array(a, _countof(a));
	random_shuffle(a, _countof(a), sizeof(int), int_swap);
	print_int_array(a, _countof(a));
	PASSED(__func__, __LINE__);
}
void count_if_test()
{
	TC_BEGIN(__func__);
	int a[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
	size_t cnt = count_if(a, _countof(a), sizeof(int), is_even);
	printf("even numbers: %zu\n", cnt);
	VERIFY(cnt == 5);
}
void equal_test()
{
	int a1[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
	int a2[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 0};
	int a3[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 1};
	VERIFY(equal(a1, a2, _countof(a1), sizeof(int), int_cmp));
	VERIFY(false == equal(a1, a3, _countof(a1), sizeof(int), int_cmp));
}
void replace_test()
{
	TC_BEGIN(__func__);
	int newval = 1111;
	int oldval = 99;
	
	int a1[] = {99, 88, 77, 66, 55, 99, 33, 22, 11, 0};
	replace(a1, &oldval, &newval, _countof(a1), sizeof(int), int_cmp);
	int cmp1[] = {1111, 88, 77, 66, 55, 1111, 33, 22, 11, 0};
	print_int_array(a1, _countof(a1));
	VERIFY(equal(a1, cmp1, _countof(a1), sizeof(int), int_cmp));
	
	int a2[] = {99, 88, 77, 66, 55, 44, 33, 44, 11, 1};
	replace_if(a2, &newval, _countof(a2), sizeof(int), is_even);

	int cmp2[] = {99, 1111, 77, 1111, 55, 1111, 33, 1111, 11, 1};
	print_int_array(a2, _countof(a2));
	print_int_array(cmp2, _countof(cmp2));
	VERIFY(equal(a2, cmp2, _countof(a2), sizeof(int), int_cmp));
}
void reverse_test()
{
	TC_BEGIN(__func__);
	int a[] = {9,8,7,6,5,4,3,2,1,0};
	int cmp[] = {0,1,2,3,4,5,6,7,8,9};
	reverse(a, _countof(a), sizeof(int), int_swap);
	print_int_array(a, _countof(a));
	VERIFY(equal(a, cmp, _countof(a), sizeof(int), int_cmp));
}
void copy_backward_test()
{
	TC_BEGIN(__func__);
	int s[] = {1,1,1,1,1,1,1,1,1,1};
	int d[] = {0,0,0,0,0,0,0,0,0,0};
	copy_backward(d, s, 5, sizeof(int));
	print_int_array(d, _countof(d));
	int cmp[] = {1,1,1,1,1,0,0,0,0,0};
	VERIFY(equal(d, cmp, _countof(d), sizeof(int), int_cmp));
}
void product_test()
{
	TC_BEGIN(__func__);
	int a[] = {1,2,3,4,5};
	int prod = product(a, _countof(a), sizeof(int), ret_int);
	printf("product: %d\n", prod);
	VERIFY(prod == 120);
	
	prod = inner_product(a, a, _countof(a), sizeof(int), ret_int);
	printf("inner product: %d\n", prod);
	VERIFY(prod == 240);
}
// often used print integer array
void print_int_array(int *arr, const size_t count)
{
	for (int *p = arr; p < arr + count; p++)
		printf("%d ", *(int *)p);

	printf("\n");
}
#pragma GCC diagnostic pop

