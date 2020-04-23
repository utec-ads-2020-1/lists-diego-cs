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
ForwardList<T>::~ForwardList() {}

template <typename T>
T ForwardList<T>::front() {
    if (!this->head) {     
        throw out_of_range("Empty forward list.");
    } else {
        return this->head->data;
    }
}

template <typename T>
T ForwardList<T>::back() {
    if (!this->tail) {      
        throw out_of_range("Empty forward list.");
    } else {
        return this->tail->data;
    }
}

template <typename T>
void ForwardList<T>::push_front(T data) {
    auto new_node = new Node<T>();
    new_node->data = data;
    new_node->next = nullptr;

    if (!this->head) {
        this->head = this->tail = new_node;
    } else {
        new_node->next = this->head;
        this->head = new_node;
    }
    ++nodes;
}

template <typename T>
void ForwardList<T>::push_back(T data) {
    auto new_node = new Node<T>();
    new_node->data = data;
    new_node->next = nullptr;

    if (!this->tail) {
        this->head = this->tail = new_node;
    } else {
        this->tail->next = new_node;
        this->tail = new_node;
    }
    ++nodes;
}

template <typename T>
void ForwardList<T>::pop_front() {
    if (!this->head) {
        cout << "Cannot pop front. Empty forward list." << endl;
    } else {
        auto temp = this->head;
        this->head = this->head->next;
        delete temp;
        --nodes;
    }
}

template <typename T>
void ForwardList<T>::pop_back() {
    if (!this->head) {
        cout << "Cannot pop back. Empty forward list." << endl;
    } else {
        auto temp = head;
        while (temp->next != this->tail) {
            temp = temp->next;
        }
        this->tail = temp;
        temp = temp->next;
        delete temp;
        --nodes;
    }
}

template <typename T>
T ForwardList<T>::operator[](int index) {
    if (index < 0 || index >= nodes) {
        throw out_of_range("Invalid index");
    } else if (index == nodes - 1) {
        return this->tail->data;
    } else {
        auto temp = this->head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }    
}

template <typename T>
bool ForwardList<T>::empty() {
    return nodes == 0;
}

template <typename T>
int ForwardList<T>::size() {
    return nodes;
}

template <typename T>
void ForwardList<T>::clear() {
    if (empty()) {
        cout << "Forward list is already empty." << endl;
    } else {
        this->head->killSelf();
    }
}

template <typename T>
void ForwardList<T>::sort() {
    if (empty()) {
        cout << "Cannot sort. Empty forward list." << endl;
    } else if (size() == 1) {
        cout << "Cannot sort. There's only one element." << endl;
    } else {
        merge_sort(this->head); //
    }
}

template <typename T>
void ForwardList<T>::reverse() {
    if (empty()) {
        cout << "Cannot reverse. Empty forward list." << endl;
    } else if (size() == 1) {
        cout << "Cannot reverse. There's only one element." << endl;
    } else {
        auto temp = this->head;
        while (temp != nullptr) {
            push_front(temp->data);
            temp = temp->next;
        }
        int _nodes = size() / 2;
        for (int i = 0; i < _nodes; ++i) {
            pop_back();
        }
    }
}

template <typename T>
ForwardIterator<T> ForwardList<T>::begin() {
    if(!this->head) {
        throw out_of_range("There's no begin. Empty forward list.");
    } else {
        auto begin = ForwardIterator<T>(this->head);
        return begin;
    }
}

template <typename T>
ForwardIterator<T> ForwardList<T>::end() {
    if (!this->tail) {
        throw out_of_range("There's no begin. Empty forward list.");
    } else {
        auto end = ForwardIterator<T>(this->tail); // (this->tail->next)
        return end;
    }
}

template <typename T>
string ForwardList<T>::name() {
    return "Forward List";
}

template <typename T>
void ForwardList<T>::merge(ForwardList<T>& new_forward_list) {
    if (empty() || new_forward_list.empty()) {
        cout << "Cannot merge." << endl;
    } else {
        auto temp = new_forward_list.head();
        while (temp != nullptr) {
            push_back(temp->data);
            temp = temp->next;
        }
        new_forward_list.clear();
        //delete new_forward_list;
    }
}

#endif