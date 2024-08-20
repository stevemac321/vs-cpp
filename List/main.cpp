// List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <functional>
#include "list.hpp"

void test_insert_head() {
    linked_list<int> list;
    list.InsertHead(10);
    list.InsertHead(20);
    list.InsertHead(30);

    assert(list.Head() == 30);
    assert(list.Tail() == 10);
    assert(list.PopHead() == 30);
    assert(list.PopHead() == 20);
    assert(list.PopHead() == 10);
    try {
        list.PopHead();
    }
    catch (const std::out_of_range&) {
        std::cout << "Passed empty list pop head test.\n";
    }
}

void test_append_tail() {
    linked_list<int> list;
    list.AppendTail(10);
    list.AppendTail(20);
    list.AppendTail(30);

    assert(list.Head() == 10);
    assert(list.Tail() == 30);
    assert(list.PopTail() == 30);
    assert(list.PopTail() == 20);
    assert(list.PopTail() == 10);
    try {
        list.PopTail();
    }
    catch (const std::out_of_range&) {
        std::cout << "Passed empty list pop tail test.\n";
    }
}

void test_find() {
    linked_list<int> list;
    list.AppendTail(10);
    list.AppendTail(20);
    list.AppendTail(30);

    auto ret = *list.Find(20);
    assert(ret == 20);
    assert(list.Find(40) == nullptr);
}

void test_empty() {
    linked_list<int> list;
    list.AppendTail(10);
    list.AppendTail(20);
    list.AppendTail(30);

    list.Empty();
    assert(list.Head() == 0);  // Head should not exist anymore
    assert(list.Tail() == 0);  // Tail should not exist anymore
}

int main() {
    test_insert_head();
    test_append_tail();
    test_find();
    try {
        test_empty();
    }
    catch (std::out_of_range) {
        std::cout << "throw expected\n";
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

