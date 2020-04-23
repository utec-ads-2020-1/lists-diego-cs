#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include "../node.h"

// TODO: Implement all methods
template <typename T> 
class ForwardIterator {
    private:
        Node<T> *current;

    public:
        ForwardIterator();
        ForwardIterator(Node<T>*);

        ForwardIterator<T> operator=(ForwardIterator<T>);

        bool operator!=(ForwardIterator<T>);

        ForwardIterator<T> operator++();

        T operator*();
};

template <typename T>
ForwardIterator<T>::ForwardIterator<T>() : this->current(nullptr) {}

template <typename T>
ForwardIterator<T>::ForwardIterator<T>(Node<T>* head) : this->current(head) {}

template <typename T>
ForwardIterator<T> ForwardIterator<T>::operator=(ForwardIterator<T> it2) {
    this->current = it2.current;
    return this;
}

template <typename T>
bool ForwardIterator<T>::operator!=(ForwardIterator<T> it2) {
    return this->current != it2.current;
}

template <typename T>
ForwardIterator<T> ForwardIterator<T>::operator++() {
    if (!this->current) {
        throw out_of_range("There's no next node.");
    } else {
        this->current = this->current->next;
        return this;
    }
}

template <typename T>
T ForwardIterator<T>::operator*() {
    return this->current->data;
}

#endif