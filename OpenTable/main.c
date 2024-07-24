/*==============================================================================
 Name        : main.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include "common.h"


#define TABLESIZE 182

#ifndef NL
#define NL printf("\n")
#endif

void print_int(const genptr pi)
{
	assert(pi);
	printf("%d ", *(int*)pi);
}
int str_cmp(const genptr v1, const genptr  v2)
{
	assert(v1 && v2);
	const char* p1 = (const char*)v1;
	const char* p2 = (const char*)v2;
	return strcmp(p1, p2);
}
int int_cmp(const genptr v1, const genptr v2)
{
	assert(v1 && v2);
	return *(int*)v1 - *(int*)v2;
}
void rand_int(int* p)
{
	assert(p);
	*p = rand() % 100;
}
void modify(genptr base, const size_t count, const size_t size,
	void(*mod)(genptr pv))
{
	assert(base && mod);
	for (genptr p = base; p < base + (count * size); p += size)
		mod(p);
}

/* TEST HARNESS*/
int passed = 0;
int failed = 0;
int tcs = 0;
// test functions
void table_test1();
void table_test2();
void print_int_array(int *arr, const size_t count);


int main()
{
	Heap_Init();

   table_test1();
   table_test2();

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
	tableptr table = open_table_init(TABLESIZE, sizeof(const char*), strhash, strhash, str_cmp, table_str_alloc);
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

	
	char *p = open_table_lookup(table, a[3]);
	if (p)
		printf("found: %s\n", p);

	open_table_remove_entry(table, a[3]);
	


	open_table_cluster_report(table);
	open_table_destroy(table);
	PASSED(__func__, __LINE__);
}

// often used print integer array
void print_int_array(int *arr, const size_t count)
{
	for (int *p = arr; p < arr + count; p++)
		printf("%d ", *(int *)p);

	printf("\n");
}
