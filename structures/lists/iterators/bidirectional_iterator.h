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

#endif