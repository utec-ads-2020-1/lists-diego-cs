#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <exception>

#define MAX 1000 

// TODO: Implement all methods
template <typename T>
class stack {
	T* data;
	int top;
	int capacity;

public:
	stack(int size = MAX);
	~stack();   		

	void push(T);
	void pop();
	T peak();

	int size();
	bool empty();
	void resize();
};

template <typename T>
stack<T>::stack(int size) : top(-1), capacity(size), data(new T[capacity]) {}

template <typename T>
stack<T>::~stack() { delete[] data; }

template <typename T>
void stack<T>::push(T element) {
	if (top == capacity - 1) {
		resize();
	}
	data[++top] = element;
}

template <typename T>
void stack<T>::pop() {
	if (!empty()) {
		std::cout << "\t" << data[top] << std::endl;
		data[top--] = data[top + 2];
	} else {
		std::cout << "Empty stack." << std::endl;
	}
}

template <typename T>
T stack<T>::peak() {
	if (!empty()) {
		return data[top];
	} else {
		throw std::out_of_range("Empty stack. There's no top element.");
	}
}

template <typename T>
int stack<T>::size() {
	return top + 1;
}

template <typename T>
bool stack<T>::empty() {
	return top == -1;
}

template <typename T>
void stack<T>::resize() {
	capacity *= 2;
	T* temp = new T[capacity];
	for (int i = 0; i < size(); ++i) {
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
}

#endif