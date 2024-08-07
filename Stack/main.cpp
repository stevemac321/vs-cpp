// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stack.hpp"
#include "queue.hpp"
#include <cassert>
#include <iostream>
void test_queue();
void test_stack();
void test_queue2();


int main()
{
    test_stack();
    test_queue();
    test_queue2();
}

// Assume Queue is a template class defined elsewhere with methods:
// void enqueue(const T& x);
// T dequeue();

void test_queue() {
    queue<int> q;

    // Test 1: Enqueue elements and check order
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    assert(q.dequeue() == 10);  // First in, first out
    assert(q.dequeue() == 20);
    assert(q.dequeue() == 30);
    std::cout << "Test 1 passed: Enqueue and dequeue elements.\n";


    // Test 3: Mixed operations
    q.enqueue(40);
    assert(q.dequeue() == 40);
    q.enqueue(50);
    q.enqueue(60);
    assert(q.dequeue() == 50);
    q.enqueue(70);
    assert(q.dequeue() == 60);
    assert(q.dequeue() == 70);
    std::cout << "Test 3 passed: Mixed enqueue and dequeue operations.\n";

    // Test 4: Large number of elements
    for (int i = 0; i < 1000; ++i) {
        q.enqueue(i);
    }
    for (int i = 0; i < 1000; ++i) {
        auto x = q.dequeue();
        assert(x == i); 
    }
    std::cout << "Test 4 passed: Large number of elements.\n";

    // Test 5: Check stability of the queue
    q.enqueue(100);
    q.enqueue(200);
    assert(q.dequeue() == 100);
    q.enqueue(300);
    assert(q.dequeue() == 200);
    assert(q.dequeue() == 300);
    std::cout << "Test 5 passed: Stability test.\n";
}
void test_queue2() {
    queue<int> q;

    // Fill the queue
    for (int i = 0; i < 1000000; i++) {
        q.enqueue(i);
    }

    // This should print "que is full"
    q.enqueue(1000000);

    // Dequeue all elements
    for (int i = 0; i < 1000000; i++) {
        assert(q.dequeue() == i);
    }

    // This should print "que is full", but it won't
    int unexpected = q.dequeue();
    std::cout << "Unexpected value: " << unexpected << std::endl;

    // This will likely cause undefined behavior
    q.enqueue(1);
    assert(q.dequeue() == 1);  // This assertion will likely fail

    std::cout << "Test completed" << std::endl;
    
}
void test_stack()
{
    // Test 1: Push and Pop Sequence
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int exp[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    stack<int> s;
    for (auto& i : a) {
        s.push(i);  // Use variable `i`, no change needed here
    }
    for (auto& i : exp) {
        assert(i == s.pop());
    }
    std::cout << "Test 1 passed: Basic push and pop sequence.\n";

    // Test 2: Pop from an empty stack
    stack<int> empty_stack;
    assert(empty_stack.pop() == 0);  // Expect default value (0 for int)
    assert(empty_stack.empty());
    std::cout << "Test 2 passed: Pop from an empty stack.\n";

    // Test 3: Push to full capacity and pop
    stack<int, 5> small_stack;
    for (int i = 0; i < 5; ++i) {
        small_stack.push(i);
    }
    assert(!small_stack.empty());

    // Attempt to push another element (should not be added)
    int value_to_push = 5;
    small_stack.push(value_to_push);  // Should print "full"
    for (int i = 4; i >= 0; --i) {
        assert(small_stack.pop() == i);
    }
    std::cout << "Test 3 passed: Push to full capacity and pop all.\n";

    // Test 4: Mixed operations
    stack<int> mixed_stack;
    int v1 = 10, v2 = 20, v3 = 30, v4 = 40;
    mixed_stack.push(v1);
    mixed_stack.push(v2);
    assert(mixed_stack.pop() == v2);
    mixed_stack.push(v3);
    mixed_stack.push(v4);
    assert(mixed_stack.pop() == v4);
    assert(mixed_stack.pop() == v3);
    assert(mixed_stack.pop() == v1);
    assert(mixed_stack.empty());
    std::cout << "Test 4 passed: Mixed push and pop operations.\n";

    // Test 5: Check for stack underflow handling
    stack<int> underflow_stack;
    assert(underflow_stack.pop() == 0);  // Expect default value
    std::cout << "Test 5 passed: Underflow test.\n";
}




