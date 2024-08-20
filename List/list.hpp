#pragma once
/*
Read my blog post on linked lists
*/

template <typename T>
struct node {
	T element = T();
	node* next = nullptr;
	node* prev = nullptr;
	node(const T& e) :element(e) {}
};

template <typename T> class linked_list {
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	size_t len = 0;
public:
	~linked_list() 
	{
		Empty();
	}

	void InsertHead(const T& e) 
	{
		node<T>* n = new node<T>(e);
		if (head == nullptr) { // implies tail == nullptr
			head = n;
			tail = n;
		}
		else {
			n->next = head;
			head->prev = n;
			head = n;
		}
		len++;
	}
	void AppendTail(const T& e) 
	{
		node<T>* n = new node<T>(e);
		if (tail == nullptr) {
			head = n;
			tail = n;
		}
		else {
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
	
		len++;
	}
	T PopHead() {
		if (head == nullptr) {
			throw std::out_of_range("List is empty");
		}
		T el = head->element;
		node<T>* del = head;

		head = head->next;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		else {// If the list is now empty, set tail to nullptr as well
			tail = nullptr;
		}
		delete del;
		len--;
		return el;
	}
	T PopTail() {
		if (tail == nullptr) {
			throw std::out_of_range("List is empty");
		}
		T el = tail->element;
		node<T>* del = tail;
		tail = tail->prev;
		if (tail != nullptr) {
			tail->next = nullptr;
		}
		else {// If the list is now empty, set head to nullptr as well
			head = nullptr;
		}
		delete del;
		len--;
		return el;
	}

	template <typename Compare = std::equal_to<int>>
	T* Find(const T& e, Compare cmp = Compare()) 
	{
		if (head) {
			node<T>* p = head;
			while (p) {
				if (cmp(p->element,e)) {
					return &(p->element);
				}
				else {
					p = p->next;
				}
			}
		}
		return nullptr; 
	}
	T& Head() {
		if (head == nullptr)
			throw std::out_of_range("List is empty");

		return head->element;
		
	}
	T& Tail() {
		if (tail == nullptr)
			throw std::out_of_range("List is empty");

		return tail->element;
	
	}

	void Empty() 
	{
		node<T>* p = head;
		while (p) {
			printf("%d",p->element);
			node<T>* del = p;
			p = p->next;
			delete del;
		}
		head = tail = nullptr;
		len = 0;
		
	}
};