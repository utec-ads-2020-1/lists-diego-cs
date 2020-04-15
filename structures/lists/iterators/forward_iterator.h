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

#endif