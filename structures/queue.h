#ifndef QUEUE_H
#define QUEUE_H

using namespace std;

#define MAX 1000 

// TODO: Implement all methods
template <typename T>
class queue {
	T* data;
	int top;
	int capacity;

public:
	queue(int size = MAX);
	~queue();   		

	void push(T);
	void pop();
	T front();
    T back();

	int size();
	bool empty();
};

#endif