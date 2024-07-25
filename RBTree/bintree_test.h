///////////////////////////////////////////////////////////////////////////////
// tests
void test_binary_tree_rb_insert()
{
    TEST_BEGIN("test_binary_tree_rb_insert INSERT")
        int a[] = { 9, 3, 5, 1 };
    BinTree<int> tree;

    // Inserting elements into the tree
    for (const auto& i : a) {
        tree.rb_insert(i);
    }
    //std::vector<int> v = tree.get_test_vector();
    int exp[] = { 1, 3, 5, 9 };
    for (auto& i : exp) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    tree.visit_in_order();

   // ASSERT_ITER_EQ(std::begin(exp), std::end(exp), v.begin(), v.end());
    TEST_END("test_binary_tree_rb_insert INSERT")
}





