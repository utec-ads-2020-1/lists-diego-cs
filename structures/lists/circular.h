#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

// TODO: Implement all methods
template <typename T>
class CircularLinkedList : public List<T> {
    private:
        Node<T>* sentinel;
    public:
        CircularLinkedList();
        ~CircularLinkedList();

        T front();
        T back();
        void push_front(T);
        void push_back(T);
        void pop_front();
        void pop_back();
        T operator[](int);
        bool empty();
        int size();
        void clear();
        void sort();
        void reverse();

        BidirectionalIterator<T> begin();
	    BidirectionalIterator<T> end();

        string name();

        /**
         * Merges x into the list by transferring all of its elements at their respective 
         * ordered positions into the container (both containers shall already be ordered).
         * 
         * This effectively removes all the elements in x (which becomes empty), and inserts 
         * them into their ordered position within container (which expands in size by the number 
         * of elements transferred). The operation is performed without constructing nor destroying
         * any element: they are transferred, no matter whether x is an lvalue or an rvalue, 
         * or whether the value_type supports move-construction or not.
        */
        void merge(CircularLinkedList<T>&);
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList() : List<T>(), sentinel(new Node <T>()) {}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    this->head->prev = nullptr;
    this->sentinel->next = nullptr;
    this->head->killSelf();
    this->nodes = 0;
}

template <typename T>
T CircularLinkedList<T>::front() {
    if (!this->head) {
        throw out_of_range("Empty " + name());
    } else {
        return this->head->data;
    }
}

template <typename T>
T CircularLinkedList<T>::back() {
    if (!this->head) {
        throw out_of_range("Empty " + name());
    } else {
        return this->tail->data;
    }
}

template <typename T>
void CircularLinkedList<T>::push_front(T data) {
    auto new_node = new Node<T>(data);
    if (!this->head) {
        this->head = this->tail = new_node;
        this->tail->next = this->sentinel;      
        this->sentinel->prev = this->tail;
    } else {
        new_node->next = this->head;
        this->head->prev = new_node;
        this->head = new_node;  
    }
    this->head->prev = this->sentinel;   
    this->sentinel->next = this->head;
    ++this->nodes;
}

template <typename T>
void CircularLinkedList<T>::push_back(T data) {
    auto new_node = new Node<T>(data);
    if (!this->head) {
        this->head = this->tail = new_node;
    } else {
        new_node->prev = this->tail;
        this->tail->next = new_node;
        this->tail = new_node;
    }
    this->head->prev = this->tail; // should be = this->sentinel;
    this->tail->next = this->head; // should be = this->sentinel;
    this->sentinel->prev = this->tail;
    this->sentinel->next = this->head;
    ++this->nodes;
}

template <typename T>
void CircularLinkedList<T>::pop_front() {
    if (!this->head) {
        cout << "Cannot pop front. Empty " << name() << endl;
    } else {
        auto temp = this->head;
        if (this->head == this->tail) {
            this->head = this->tail = nullptr;
            this->sentinel->prev = this->sentinel->next = nullptr;
        } else {
            this->head = this->head->next;
            this->head->prev = this->sentinel;
            this->sentinel->next = this->head;     
        }
        delete temp;
        --this->nodes;
    }
}

template <typename T>
void CircularLinkedList<T>::pop_back() {
    if (!this->tail) {
        cout << "Cannot pop fron. Empty " << name() << endl;
    } else {
        auto temp = this->tail;
        if (this->head == this->tail) {
            this->head = this->tail = nullptr;
            this->sentinel->prev = this->sentinel->next = nullptr;
        } else {
            this->tail = this->tail->prev;
            this->tail->next = this->sentinel;
            this->sentinel->prev = this->tail;          
        }
        delete temp;
        --this->nodes;
    }
}

template <typename T>
T CircularLinkedList<T>::operator[](int index) {
    if (!this->head) {
        throw out_of_range("Empty " + name());
    } else if (index < 0 || index >= this->nodes) {
        throw out_of_range("Invalid index");
    } else {
        if (index == this->nodes - 1) {
            return this->tail->data;
        } else {
            auto temp = this->head;
            for (int i = 0; i < index; ++i) {
                temp = temp->next;
            }
            return temp->data;
        }
    }
}

template <typename T>
bool CircularLinkedList<T>::empty() {
    return !this->head;
}

template <typename T>
int CircularLinkedList<T>::size() {
    return this->nodes;
}

template <typename T>
void CircularLinkedList<T>::clear() {
    if (empty()) {
        cout << "Circular Linked List is already empty." << endl;
    } else {
        this->sentinel->next = nullptr;
        this->head->killSelf();
        this->head = this->tail = nullptr;
        this->nodes = 0;
    }
}

template <typename T>
void CircularLinkedList<T>::sort() {
    if (empty()) {
        cout << "Cannot sort. Empty " << name() << endl;
    } else if (this->head == this->tail) {
        cout << "Cannot sort. There's only one element." << endl;
    } else {
        this->tail->next = nullptr; /* tail->next stop pointing to sentinel */
        merge_sort(this->head);
        auto temp = this->head;
        while(temp->next){
            this->tail = temp->next;
            this->tail->prev = temp;
            temp = temp->next;
        }
        this->head->prev = this->sentinel;
        this->tail->next = this->sentinel;
        this->sentinel->prev = this->tail;
        this->sentinel->next = this->head;
        temp = nullptr;
        delete temp;
    }
}

template <typename T>
void CircularLinkedList<T>::reverse() {
    if (empty()) {
        cout << "Cannot reverse. Empty " << name() << endl;
    } else if (this->head == this->tail) {
        cout << "Cannot reverse. There's only one element." << endl;
    } else {
        this->head->prev = nullptr;
        this->sentinel->next = nullptr;
        this->head->reverse_next();
        this->sentinel->reverse_prev();
        auto temp = this->head;
        this->head = this->tail;
        this->tail = temp;
        this->head->prev = this->sentinel;
        this->tail->next = this->sentinel;
        this->sentinel->prev = this->tail;
        this->sentinel->next = this->head;
        temp = nullptr;
        delete temp;
    }
}

template <typename T>
BidirectionalIterator<T> CircularLinkedList<T>::begin() {
    if (!this->head) {
        throw out_of_range("There's no begin. Empty " + name());
    } else {
        return BidirectionalIterator<T>(this->head);
    }
}

template <typename T>
BidirectionalIterator<T> CircularLinkedList<T>::end() {
    if (!this->tail) {
        throw out_of_range("There's no end. Empty " + name());
    } else {
        return BidirectionalIterator<T>(this->sentinel);
    }
}

template <typename T>
string CircularLinkedList<T>::name() {
    return "Circular Linked List";
}

template <typename T>
void CircularLinkedList<T>::merge(CircularLinkedList<T>& new_cllist) {
    if (!this->head) {
        this->head = new_cllist.head;
        this->tail = new_cllist.tail;
        this->sentinel = new_cllist.sentinel;
    } else {
        this->tail->next = new_cllist.tail;
        new_cllist.head->prev = this->tail;
        this->tail = new_cllist.tail;
        this->head->prev = new_cllist.sentinel;
        auto temp = this->sentinel;
        this->sentinel = new_cllist.sentinel;
        delete temp;
        this->sentinel->next = this->head;
    }
    this->nodes += new_cllist.nodes;
    new_cllist.head = new_cllist.tail = new_cllist.sentinel = nullptr;
    new_cllist.nodes = 0;
}

#endif