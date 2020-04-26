#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T data);
    void killSelf();
    void reverse_next();
    void reverse_prev();
};

template <typename T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = this->prev = nullptr;
}

template <typename T>
void Node<T>::killSelf() {
    if (this->next) {
        next->killSelf();
    }
    delete this;
}

template <typename T>
void Node<T>::reverse_next() {
    if (this->next->next) {
        this->next->reverse_next();
    }
    this->next->next = this;
}

template <typename T>
void Node<T>::reverse_prev() {
    if (this->prev->prev) {
        this->prev->reverse_prev();
    }
    this->prev->prev = this;
}

#endif