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
void parity();
void three_conseq_ones();
void sorted_letters();
int main()
{
    enable_virtual_terminal_processing();
    test_inorder_vowels();
    test_bounce_filter();
    fbounce();
    parity();
    three_conseq_ones();
    sorted_letters();
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
    puts("\n Enter bounce filter bits: ");
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
   start state is NOCHANGE.
   odd parity is non-accepting.
   even is accepting.
   zeros do not affect state.
 */

void parity() {
    puts("\n Enter parity bits: ");
    int x;

NOCHANGE:
    x = getchar();
    if (x == '0') goto NOCHANGE;
    if (x == '1') goto ODD;
    goto finis;
  
ODD:  puts("ODD");
    x = getchar();
    if (x == '0') goto NOCHANGE;
    if (x == '1') goto EVEN;
    goto finis;
 
EVEN:  puts("EVEN");
    x = getchar();
    if (x == '0') goto NOCHANGE;
    if (x == '1') goto ODD;
    goto finis;
   
finis:;
}


/*
* New exercise with code to follow, it looks correct:
b) Check that there are no more than two consecutive 1’s. That is, accept unless
111 is a substring of the input string read so far.
What is the intuitive meaning of each of your states?
10.2.2: Indicate the sequence of states and the outputs when your automata from
Exercise 10.2.1 are given the input 101001101110.

Input: 101001101110
Output:
ZERO
ONE
ZERO
ONE
ZERO
ZERO
ONE
TWO
ZERO
ONE
TWO
REJECT

*/
void three_conseq_ones()
{
    puts("\n Enter reject 3 conseq bits: ");
    int x;

ZERO:
    x = getchar();
    puts("ZERO");
    if (x == '0') goto ZERO;
    if (x == '1') goto ONE;
    goto finis;
    
ONE:  puts("ONE");
    x = getchar();
    if (x == '0') goto ZERO;
    if (x == '1') goto TWO;
    goto finis;
   
TWO:  puts("TWO");
    x = getchar();
    if (x == '0') goto ZERO;
    if (x == '1') goto REJECT;
    goto finis;
REJECT:
    puts("REJECT");
finis:;
}
/*
* 
10.2.3*: Design an automaton that reads a word (character string) and tells
whether the letters of the word are in sorted order. For example, adept and chilly
have their letters in sorted order; baby does not, because an a follows the first b.
The word must be terminated by a blank, so that the automaton will know when
it has read all the characters. (Unlike Example 10.1, here we must not accept until
we have seen all the characters, that is, until we reach the blank at the end of the
word.) How many states do you need? What are their intuitive meanings? How
many transitions are there out of each state? How many accepting states are there?

Inputs: 
adept == ACCEPT
chilly == ACCEPT
baby == ACCEPT

*/
bool is_endword(int c) {
    if (c == EOF || c == '\n' || c == '\0' || c == ' ' || c == '\t')
        return true;
    else
        return false;
}
void sorted_letters()
{
    puts("\n Enter words : ");
  

  // START: this is just a comment, the compiler complains that it is an unreferenced label because
  // no other part of the program does a "goto START".
    int last = getchar();
    int cur;

OK:
    cur = getchar();
    if (is_endword(cur)) {
        goto ACCEPT;
    }
    if ( cur >= last) {
        last = cur;
         goto OK;
    }
    else {
        goto REJECT;
    }
    goto finis;

REJECT:
    puts("REJECT");
    goto finis;

ACCEPT:
    puts("ACCEPT");
    goto finis;

finis:;
    
}



