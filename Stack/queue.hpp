#pragma once
#include <iostream>

template <typename T, int N= 1000000> class CLRS_queue {
	T que[N];
	int head = 0;
	int tail = 0;
	int len = N;


public:

	void enqueue(const T& x)
	{
		que[tail] = x;
		if (tail == (len - 1) || tail < 0) {
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
		if (head == (len - 1) || head < 0) {
			std::cout << "que is full";
			return T();
		}
		else {
			head++;
		}
		return x;
	}
	
};
template <typename T, int N= 1000000> class queue {
	T que[N];
	int head = 0;
	int tail = 0;
	int count = 0;
	int len = N;


public:

	void enqueue(const T& x)
	{
		
		if (is_full()) {
			std::cout << "que is full";
			return;
		}
		else {
			que[tail] = x;
			tail = (tail + 1) % len;
			count++;
		}
	}
	T dequeue()
	{
		T x = T();
		if (is_empty()) {
			std::cout << "que is empty";
			x;
		}
		else {
			x = que[head];
			head = (head + 1) % len;
			count--;
		}
		return x;
	}
	bool is_empty() { return count == 0; }
	bool is_full() { return count == 0; }


};