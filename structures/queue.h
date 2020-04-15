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
	stack(int size = MAX);
	~stack();   		

	void push(T);
	int pop();
	int front();
    int back();

	int size();
	bool empty();
};

#endif