// Automata.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>
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
void test_inorder_vowels();
void test_bounce_filter();
int main()
{
    enable_virtual_terminal_processing();
   // test_inorder_vowels();
    test_bounce_filter();

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
* Eliminate "noise" when a single 1 is surrounded by 0's.

States:
a) We have just seen a sequence of 0’s, at least two in a row.
b) We have just seen a sequence of 0’s followed by a single 1.
c) We have just seen a sequence of at least two 1’s.
d) We have just seen a sequence of 1’s followed by a single 0.
The adjacency list for this automaton can be represented as follows:

Let's do it this way.  So indicate what the work of the state is, not just the rules of transition.
Transition Rules:
- **State a**:
  - `(a, a)` on input 0 (stay in state a)
  - `(a, b)` on input 1 (transition to state b)

- **State b**:
  - `(b, a)` on input 0 (transition to state a)
  - `(b, c)` on input 1 (transition to state c)

- **State c**:
  - `(c, c)` on input 1 (stay in state c)
  - `(c, d)` on input 0 (transition to state d)

- **State d**:
  - `(d, a)` on input 0 (transition to state a)
  - `(d, c)` on input 1 (transition to state c)

  Input:  0  1  0  1  1  0  1
State:  a  a  b  a  b  c  d  c
Output: 0  0  0  0  0  1  1  1

To address the issue with your bounce filter implementation, let's focus on the logic for each state and ensure that the output is generated correctly based on the state transitions. Here's a breakdown of what each state should do, along with some suggestions for your code:

### State Responsibilities and Output Logic

State Transitions and Output:
State FA:
On input 0, print 0 and stay in FA.
On input 1, transition to FB without printing anything yet (defer output decision to FB).
State FB:
On input 0, print 0 and transition back to FA.
On input 1, print 0 (since the single 1 is considered noise) and transition to FC.
State FC:
On input 0, defer output decision and transition to FD.
On input 1, print 1 and stay in FC.
State FD:
On input 0, print 1 (since the single 0 is considered noise) and transition to FA.
On input 1, transition to FC without printing anything yet.

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


