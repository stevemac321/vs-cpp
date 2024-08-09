#pragma once
#include <iostream>

template <typename T, int N = 100>
class stack {
    T stk[N];
    int top = -1;  // Changed to -1 to represent an empty stack
    static const int size = N;  // Made size a static const

public:
    bool empty() const { return top == -1; }
    bool full() const { return top == size - 1; }

    void push(const T& x) {
        if (!full()) {
            stk[++top] = x;  // Increment top first, then assign
        }
        else {
            std::cout << "Stack is full\n";
        }
    }

    T pop() {
        if (!empty()) {
            return stk[top--];  // Return and then decrement top
        }
        else {
            std::cout << "Stack is empty\n";
            return T();  // Return default-constructed T
        }
    }

    // Optional: peek function to look at the top element without removing it
    T peek() const {
        if (!empty()) {
            return stk[top];
        }
        else {
            std::cout << "Stack is empty\n";
            return T();
        }
    }
};

