#pragma once
#include <iostream>

template <typename T, int N=100> class stack{
	T stk[N];
	int top = -1;
	int size;
	

public:
	stack() :size(N) {}
	bool empty() { return top == -1; }
	
	void push(const T& x) {
		if (top < (size -1)) {
			top++;
			stk[top] = x;
		}
		else {
			std::cout << "full";
		}
	}
	T pop() { 
		if (empty()) {
			std::cout << "empty";
			return T();
		}
		else {
			top--;
			return stk[top + 1];
		}
	}
};