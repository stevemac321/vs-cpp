#include "common.h"
#include "binarytree.h"
#include "bintree_test.h"


int main(int argc, char *argv[])
{
    enable_virtual_terminal_processing();
    test_binary_tree_rb_insert();
    print_summary();
}
