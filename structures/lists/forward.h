#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList(); 
        ~ForwardList();

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

        ForwardIterator<T> begin();
	    ForwardIterator<T> end();

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
        void merge(ForwardList<T>&);
};

template <typename T>
ForwardList<T>::ForwardList() : List<T>() {}

template <typename T>
ForwardList<T>::~ForwardList() {
    this->head->killSelf();
    this->nodes = 0;
}

template <typename T>
T ForwardList<T>::front() {
    if (!this->head) {     
        throw out_of_range("Empty " + name());
    } else {
        return this->head->data;
    }
}

template <typename T>
T ForwardList<T>::back() {
    if (!this->tail) {      
        throw out_of_range("Empty " + name());
    } else {
        return this->tail->data;
    }
}

template <typename T>
void ForwardList<T>::push_front(T data) {
    auto new_node = new Node<T>(data);
    if (!this->head) {
        this->head = this->tail = new_node;
    } else {
        new_node->next = this->head;
        this->head = new_node;
    }
    ++this->nodes;
}

template <typename T>
void ForwardList<T>::push_back(T data) {
    auto new_node = new Node<T>(data);
    if (!this->tail) {
        this->head = this->tail = new_node;
    } else {
        this->tail->next = new_node;
        this->tail = new_node;
    }
    ++this->nodes;
}

template <typename T>
void ForwardList<T>::pop_front() {
    if (!this->head) {
        cout << "Cannot pop front. Empty " << name() << endl;
    } else {
        auto temp = this->head;
        if (this->head == this->tail) {         
            this->head = this->tail = nullptr;
            delete temp;
        } else {
            this->head = this->head->next;
            delete temp;    
        }
        --this->nodes;
    }
}

template <typename T>
void ForwardList<T>::pop_back() {
    if (!this->tail) {
        cout << "Cannot pop back. Empty " << name() << endl;
    } else {
        if (this->head == this->tail) {
            auto temp = this->tail;
            this->tail = this->head = nullptr;
            delete temp;
        } else {
            auto temp = this->head;
            while (temp->next != this->tail) {
                temp = temp->next;
            }
            temp->next = this->tail->next;
            this->tail = temp;
            temp = temp->next;
            delete temp;
        }
        --this->nodes;
    } 
}

template <typename T>
T ForwardList<T>::operator[](int index) {
    if (index < 0 || index >= this->nodes) {
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
bool ForwardList<T>::empty() {
    return !this->head;
}

template <typename T>
int ForwardList<T>::size() {
    return this->nodes;
}

template <typename T>
void ForwardList<T>::clear() {
    if (empty()) {
        cout << "Forward list is already empty." << endl;
    } else {
        this->head->killSelf();
        this->head = this->tail = nullptr;
        this->nodes = 0;
    }
}

template <typename T>
void ForwardList<T>::sort() {
    if (empty()) {
        cout << "Cannot sort. Empty " << name() << endl;
    } else if (this->head == this->tail) {
        cout << "Cannot sort. There's only one element." << endl;
    } else {
        merge_sort(this->head);
        this->tail = this->head;
        while(this->tail->next) {
            this->tail = this->tail->next;
        }
    }
}

template <typename T>
void ForwardList<T>::reverse() {
    if (empty()) {
        cout << "Cannot reverse. Empty " << name() << endl;
    } else if (this->head == this->tail) {
        cout << "Cannot reverse. There's only one element." << endl;
    } else {
        this->head->reverse_next();
        auto temp = this->head;
        this->head = this->tail;
        this->tail = temp;
        this->tail->next = nullptr;
        temp = nullptr;
        delete temp;  
    }
}

template <typename T>
ForwardIterator<T> ForwardList<T>::begin() {
    if(!this->head) {
        throw out_of_range("There's no begin. Empty " + name());
    } else { 
        return ForwardIterator<T>(this->head);
    }
}

template <typename T>
ForwardIterator<T> ForwardList<T>::end() {
    if (!this->tail) {
        throw out_of_range("There's no begin. Empty " + name());
    } else {
        return ForwardIterator<T>(this->tail->next);
    }
}

template <typename T>
string ForwardList<T>::name() {
    return "Forward List.";
}

template <typename T>
void ForwardList<T>::merge(ForwardList<T>& new_flist) {
    if (!this->head) {
        this->head = new_flist.head;
        this->tail = new_flist.tail;
        this->nodes = new_flist.nodes;
    } else {
        this->tail->next = new_flist.head;
        this->tail = new_flist.tail;
        this->nodes += new_flist.nodes; 
    }
    new_flist.head = new_flist.tail = nullptr;
    new_flist.nodes = 0;
}

#endif
