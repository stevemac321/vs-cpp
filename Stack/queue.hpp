#pragma once
#include <iostream>

template <typename T> class queue {
	T que[1000000];
	int head = 0;
	int tail = 0;
	int len = 1000000;


public:
	
	void enqueue(const T& x) 
	{
		que[tail] = x;
		if (tail == (len-1) || tail < 0) {
			std::cout << "que is full";
			return;
		}
		else {
			tail++;
		}
	}
	T dequeue() 
	{
		auto x = que[head];
		if (head == (len -1) || head < 0) {
			std::cout << "que is full";
			return T();
		}
		else {
			head++;
		}
		return x;
	}
};