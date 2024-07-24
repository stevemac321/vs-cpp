#include "common.h"
void STEVEMAC_TRACE(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

int passed = 0;
int failed = 0;
int tcs = 0;

//int algo_copy_reverse_pass();
int algo_non_mod_pass();
int clear_pass();
int copy_assign_pass();
int copy_ctor_pass();
int emplace_pass();
int erase_pass();
int init_assign_pass();
int insert_pass();
int logical_ops_pass();
int move_assign_pass();
int move_assign_ctor_pass();
int swap_pass();


int main()
{
	Heap_Init();
	//algo_copy_reverse_pass();
	algo_non_mod_pass();
	clear_pass();
	copy_assign_pass();
	copy_ctor_pass();
	emplace_pass();
	erase_pass();
	init_assign_pass();
	insert_pass();
	logical_ops_pass();
	move_assign_pass();
	move_assign_ctor_pass();
	swap_pass();

}
