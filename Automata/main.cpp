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

int main()
{
    enable_virtual_terminal_processing();
    TEST_BEGIN("Inorder Vowels");

    {
        const char words[] = { 'a', 'b', 's', 't', 'e', 'm', 'i', 'o', 'u', 's','\0'};
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


