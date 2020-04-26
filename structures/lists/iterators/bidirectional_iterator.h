#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "../node.h"

// TODO: Implement all methods
template <typename T> 
class BidirectionalIterator {
    private:
        Node<T> *current;

    public:
        BidirectionalIterator();
        BidirectionalIterator(Node<T>*);

        BidirectionalIterator<T> operator=(BidirectionalIterator<T>);

        bool operator!=(BidirectionalIterator<T>);

        BidirectionalIterator<T> operator++();

        BidirectionalIterator<T> operator--();

        T operator*();
};

template <typename T>
BidirectionalIterator<T>::BidirectionalIterator() : current(nullptr) {}

template <typename T>
BidirectionalIterator<T>::BidirectionalIterator(Node<T>* node) : current(node) {}

template <typename T>
BidirectionalIterator<T> BidirectionalIterator<T>::operator=(BidirectionalIterator<T> it2) {
    this->current = it2.current;
    return *this;
}

template <typename T>
bool BidirectionalIterator<T>::operator!=(BidirectionalIterator<T> it2) {
    return this->current != it2.current;
}

template <typename T>
BidirectionalIterator<T> BidirectionalIterator<T>::operator++() {
    if (!this->current) {
        throw out_of_range("Iterator is pointing to null.");
    } else {
        this->current = this->current->next;
        return *this;
    }
}

template <typename T>
BidirectionalIterator<T> BidirectionalIterator<T>::operator--() {
    if (!this->current) {
        throw out_of_range("Iterator is pointing to null.");
    } else {
        this->current = this->current->prev;
        return *this;
    }
}

template <typename T>
T BidirectionalIterator<T>::operator*() {
    if (!this->current) {
        throw out_of_range("Iterator is pointing to null.");
    } else {
        return this->current->data;
    }
}

#endif