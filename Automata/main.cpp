// Automata.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>
#include <cstdio>
#include "..\Stack\stack.hpp"
#include "..\RBTree\common.h"

template <typename T, size_t N> constexpr size_t array_size(T(&)[N])
{
    return N;
}

enum State{NONE, A, E, I, O, U, DONE};
enum FilterState { FA, FB, FC, FD };

bool inorder_words(const char words[], const size_t len);
void bounce_filter(int arr[], const size_t len);
void fbounce();
void test_inorder_vowels();
void test_bounce_filter();
void fbounce();
int main()
{
    enable_virtual_terminal_processing();
    test_inorder_vowels();
    test_bounce_filter();
    fbounce();
}
bool inorder_words(const char words[], const size_t len)
{
    std::cout << "The word is: " << words << "\n";
    stack<char> stk({ 'u', 'o', 'i', 'e', 'a' });

    size_t state = NONE;
    auto expected = stk.pop();
    for (size_t i = 0; i < len; i++) {
        if (std::tolower(words[i]) == expected) {
            state++;  // NONE transitions to A, then A transitiosn to B, etc.
            expected = stk.pop();
        }
    }
    return (state == DONE);
}
void test_inorder_vowels()
{

    TEST_BEGIN("Inorder Vowels");

    {
        const char words[] = { 'a', 'b', 's', 't', 'e', 'm', 'i', 'o', 'u', 's','\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, true);
    }
    {
        const char words[] = { 'f', 'a', 'c', 'e', 't', 'i','o', 'u', 's','\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, true);
    }
    {
        const char words[] = { 'a', 'e', 'r', 'i', 'f', 'o', 'r', 'm','\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, false);
    }
    {
        const char words[] = { 'a', 'r', 's', 'e', 'n', 'i', 'o', 'u', 's','\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, true);
    }
    {
        const char words[] = { 'a', 'n', 'e', 'm', 'i', 'o', 'u', 's','\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, true);
    }
    {
        const char words[] = { 'c', 'a', 'e', 's', 'i', 'u', 'm','\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, false);
    }
    {
        const char words[] = { 'b', 'a', 'c', 'o','n' ,'\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, false);
    }
    {
        const char words[] = { 'q', 'u', 'e', 'u', 'e' ,'\0' };
        auto b = inorder_words(words, array_size(words));
        ASSERT_EQ(b, false);
    }

    TEST_END("Inorder Vowels");

}
/*
*Upon

*/
void bounce_filter(int arr[], const size_t len) {
    auto noisestate = FilterState::FA;

    for (size_t i = 0; i < len; i++) {
        if (arr[i] != 0 && arr[i] != 1) {
            std::cout << "bad input" << "\n";
            return;
        }

        switch (noisestate) {
        case FilterState::FA: {
            std::cout << 0;
            if (arr[i] == 1) {
                noisestate = FilterState::FB;
            }
            break;
        }
        case FilterState::FB: {
            if (arr[i] == 0) {
                std::cout << 0;
                noisestate = FilterState::FA;
            }
            else {
                std::cout << 0; // Print 0 for noise
                std::cout << 1; // Entering FC
                noisestate = FilterState::FC;
            }
            break;
        }
        case FilterState::FC: {
            if (arr[i] == 0) {
                noisestate = FilterState::FD;
            }
            else {
                std::cout << 1;
            }
            break;
        }
        case FilterState::FD: {
            if (arr[i] == 0) {
                std::cout << 1; // Print 1 for noise
                noisestate = FilterState::FA;
            }
            else {
                std::cout << 1; // Print 1 for noise
                noisestate = FilterState::FC;
            }
            break;
        }
            default: {
                std::cout << "invalid state" << "\n";
             return;
            }
        }
    }
    // Final output in case the loop ends in FC state
    if (noisestate == FilterState::FC) {
        std::cout << 1;
    }
}

void test_bounce_filter()
{
    int a[] = { 0,1,0,1,1,0,1 };
    for (size_t i = 0; i < array_size(a); i++) {
        std::cout << a[i];
    }
    std::cout << "\n";
    int exp[] = { 0,0,0,0,0,1,1,1};
    for (size_t i = 0; i < array_size(exp); i++) {
        std::cout << exp[i];
    }
    std::cout << "\n";
    bounce_filter(a, array_size(a));
}

/*
   state a and b are rejecting states(print 0),
    c and d accepting states( print 1.
    From Foundations
 */
void fbounce() {
    int x;
    puts("\n");
    /* state a */
a:  putchar('0');
    x = getchar();
    if (x == '0') goto a; /* transition to state a */
    if (x == '1') goto b; /* transition to state b */
    goto finis;
    /* state b */
b:  putchar('0');
    x = getchar();
    if (x == '0') goto a; /* transition to state a */
    if (x == '1') goto c; /* transition to state c */
    goto finis;
    /* state c */
c:  putchar('1');
    x = getchar();
    if (x == '0') goto d; /* transition to state d */
    if (x == '1') goto c; /* transition to state c */
    goto finis;
    /* state d */
d:  putchar('1');
    x = getchar();
    if (x == '0') goto a; /* transition to state a */
    if (x == '1') goto c; /* transition to state c */
    goto finis;
finis:;
}

/*
enum State{A,E,I,O,U}
fn inorder_vowels(_words: &[char]) ->(i32,i32) {

}


fn main() {
    let words: [char; 68] = ['a', 'b', 's', 't', 'e', 'm', 'i', 'o', 'u', 's', ' ', 'f', 'a', 'c', 'e', 't', 'i',
    'o', 'u', 's', ' ', 'a', 'e', 'r', 'i', 'f', 'o', 'r', 'm', ' ', 'a', 'r', 's', 'e', 'n', 'i', 'o', 'u', 's',
    ' ', 'a', 'n', 'e', 'm', 'i', 'o', 'u', 's', ' ', 'c', 'a', 'e', 's', 'i', 'u', 'm', ' ', 'b', 'a', 'c', 'o',
     'n', ' ', 'q', 'u', 'e', 'u', 'e'];

    let _total = inorder_vowels(&words);

}
/*
Five words containing all 5 vowels in order: "abstemious", "facetious", "aeriform", "arsenious", and "anemious"
Two false cases: "caesium" (vowels not in order) and "bacon" (missing vowels)
One additional word: "queue" (repeated vowels, not all 5)
*/


