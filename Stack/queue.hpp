#pragma once
#include <iostream>

template <typename T, int N = 1000000>
class queue {
    T que[N];
    int head = 0;
    int tail = 0;
    int count = 0;
    const int len = N;  // Made this const

public:
    void enqueue(const T& x) {
        if (is_full()) {
            std::cout << "Queue is full\n";
            return;
        }
        que[tail] = x;
        tail = (tail + 1) % len;
        count++;
    }

    T dequeue() {
        if (is_empty()) {
            std::cout << "Queue is empty\n";
            return T();
        }
        T x = que[head];
        head = (head + 1) % len;
        count--;
        return x;
    }

    bool is_empty() const { return count == 0; }
    bool is_full() const { return count == len; }  
};
