#ifndef QUEUE_H
#define QUEUE_H

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
	void resize();
};

template <typename T>
queue<T>::queue(int size) : top(-1), capacity(size), data(new T[capacity]) {}

template <typename T>
queue<T>::~queue() { delete[] data; }

template <typename T>
void queue<T>::push(T element) {
	if (top == capacity - 1) {
		resize();
	}
	data[++top] = element;
}

template <typename T>
void queue<T>::pop() {
	if (!empty()) {
		std::cout << "\t" << data[0] << " ";
		for (int i = 0; i < top + 1; ++i) {
			data[i] = data[i + 1];
		}
		--top;
	} else {
		std::cout << "Empty queue." << std::endl;
	}
}

template <typename T>
T queue<T>::front() {
	if (!empty()) {
		return data[0];
	} else {
		throw std::out_of_range("Empty queue. There's no front element.");
	}
}

template <typename T>
T queue<T>::back() {
	if (!empty()) {
		return data[top];
	} else {
		throw std::out_of_range("Empty queue. There's no back element.");
	}
}

template <typename T>
int queue<T>::size() {
	return top + 1;
}

template <typename T>
bool queue<T>::empty() {
	return top == -1;
}

template <typename T>
void queue<T>::resize() {
	capacity *= 2;
		T* temp = new T[capacity];
		for (int i = 0; i < size(); ++i) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
}

#endif