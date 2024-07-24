/*
Insertion Sort
Input: a sequence of n numbers <a_1, a_2...,a_n>
Output:A permutation (reordering) that a_1'<= a_2'...<= a_n'
We refer to the numbers as "keys", although concepturally we are  sorting a sequence, the input comes to us in the form
of an array with n elements.
Most sorted has the concept of a partition: the sorted partition and the unsorted partition (my note).

Most sorts are to be done in place.

Loop invariant (LI): At the start of each iteration of the for loop of lines "for" to the 
array[i+1] = key, the subarray A[0..j-1] consists of the elements originally in A[0..j-1], but now in sorted order.

Initialization:  LI is true prior to the first iteration of the loop. (for insertion sort, the sorted element is A[0]).
Maintenance:  If it is true before an iteration, it remains true before the next. (for insertion sort, moving A[j-1], 
then A[j-2], ... and so one by one position until it is in the correct sorted position for a[j] saved in key which is
then inserted.)
Termination:  When the loop terminates, the invariant gives us a useful property that helps show that the algorithm
is correct. (when j == len)
 */
#pragma once
// lambdas for comparisons
auto insertion_strcmp = [](const char* a, const char* b) { return std::strcmp(a, b) > 0; };
auto insertion_string_comp = [](const std::string& a, const std::string& b) { return a.compare(b) > 0; };

// Generic insertion sort template with a comparator: NOTE greater for ascending, less for descending.
template <typename T, const size_t N, typename Compare = std::greater<T>>
void insertion_sort(T (&array)[N], Compare comp = Compare()) {
    for (size_t j = 1; j < N; ++j) {
        T key = array[j];
        int i = j - 1;
        while (i >= 0 && comp(array[i], key)) {  // greater for ascending
            array[i + 1] = array[i];
            --i;
        }
        array[i + 1] = key;
    }
}
// Specialization for std::array<char, N>
template <const size_t N>
void insertion_sort(std::array<char, N>& a)
{
  for(int j = 1; j < N; j++) {
        int key = a[j]; //save this until correct place in sorted array is found.
        // insert a[j] into sorted sequence A[0..j-1] (keep in mind we are zero based however)
        int i = j - 1;
        while(i >= 0 && a[i] > key) {
            a[i+1] =a[i];
            i--;
        }
        a[i+1] = key;
    }
}
/////////////////////////////////////////////////////////////////////////////////
void test_insertion_sort()
{
    TEST_BEGIN("test_insertion_sort 1")
    int a[] = {44,2,6,8,0,1};
    int b[] = {0,1,2,6,8,44};
    insertion_sort(a);
    ASSERT_ITER_EQ(std::begin(a), std::end(a), std::begin(b), std::end(b)); 
    TEST_END("test_insertion_sort 1")

    TEST_BEGIN("test_insertion_sort 2")
    int a2[] = {44,2,6,8,0,1};
    int g[] = {44,8,6,2,1,0};
    insertion_sort(a2, std::less());
    ASSERT_ITER_EQ(std::begin(a2), std::end(a2), std::begin(g), std::end(g)); 
    TEST_END("test_insertion_sort 2")
     
    TEST_BEGIN("test_insertion_sort 3")
    const char* charArray[] = {"banana", "apple", "cherry"};
    const char* cmpArray[] = {"apple", "banana","cherry"};
    insertion_sort(charArray, insertion_strcmp);
    for(int i=0; i < 3; i++) {
        ASSERT_STREQ(charArray[i], cmpArray[i]);
    }
    TEST_END("test_insertion_sort 3")

    TEST_BEGIN("test_insertion_sort 4")
    std::string stringArray[] = {"banana", "apple", "cherry"};
    std::string cmpStringArray[] = {"apple", "banana","cherry"};
    insertion_sort(stringArray, insertion_string_comp);
    for(int i=0; i < 3; i++) {
        ASSERT_STR_EQ(stringArray[i], cmpStringArray[i]);
    }
    TEST_END("test_insertion_sort 4")

    TEST_BEGIN("test_insertion_sort 5")
    std::array<char, 5> charstdArray = {'e', 'd', 'a', 'c', 'b'};
    std::array<char, 5> cmpstdArray = {'a', 'b', 'c', 'd', 'e'};

    insertion_sort(charstdArray);  // Uses the std::array specialization
    ASSERT_ITER_EQ(std::begin(charstdArray), std::end(charstdArray), std::begin(cmpstdArray), std::end(cmpstdArray)); 
    TEST_END("test_insertion_sort 5")
    
} 
