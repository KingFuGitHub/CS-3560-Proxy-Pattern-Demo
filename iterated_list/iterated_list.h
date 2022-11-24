#ifndef ITERATED_LIST_H
#define ITERATED_LIST_H

#include <iostream>
#include "../node.h"
#include "../my_list.h"

using namespace std;


template <typename T>
class Simple_List {
public:
// the nested class is declared AND defined inside the enclosing
// class declaration. Alternative would be too messy!

    class Iterator {
    // the nested class
    public:
        friend class Simple_List;
        // this will allow simple list to access the private members of Iterator

        Iterator next() {
            // return an iterator to the next location in the list
            return Iterator(_ptr->_next);
        }

        Iterator(node<T> *p = nullptr): _ptr(p) {    // ctor
            // PUPOSELY LEFT BLANK
        }

        T& operator *() {   // dereference operator
            return _ptr->_item;

        }


        const T& operator *() const {   // dereference operator
           assert(_ptr != nullptr);
           return _ptr->_item;

        }

        T* operator ->() {
            assert(_ptr != nullptr);
            T* item = _ptr->_item;
            return item;
        }

        const T* operator ->() const {
            assert(_ptr != nullptr);
            T* item = _ptr->_item;
            return item;
        }

        friend Iterator operator ++(Iterator& it, int unused) { // it++
            Iterator temp = it.next();
            if (temp._ptr != nullptr){
                return temp;
            }
            return it;
        }


        Iterator& operator ++() {   // ++it
            _ptr++;
            return *this;
        }

        friend bool operator !=(const Iterator& left, const Iterator right) {
          return (left._ptr != right._ptr);
        }

    private:
        node<T>* _ptr;
    };

   Simple_List();                                          // ctor
   Simple_List(T item);

   //BIG 3:
   ~Simple_List();
   Simple_List(const Simple_List<T> &copyThis);
   Simple_List& operator =(const Simple_List& RHS);

   Iterator InsertHead(T i);                     // insert at the head of list
   Iterator InsertAfter(T i, Iterator iMarker);  // insert after marker
   Iterator InsertBefore(T i, Iterator iMarker); // insert before marker
   Iterator InsertEnd(T i);
   Iterator InsertSorted(T i, bool ascending);   // insert in a sorted list
   Iterator InsertSortedAndAdd(T i, bool ascending);

   T Delete(Simple_List<T>::Iterator iMarker);
   //delete node pointed to by marker
   T RemoveHead();
   void Print() const;
   Iterator Search(const T &key);              // return Iterator to node [key]
   Iterator Prev(Iterator iMarker);            // previous node to marker
   Iterator Next(Iterator iMarker);            // next node to marker

   T& operator[](int index);                   // return item at position index
   Iterator Begin() const;                     // Iterator to the head node
   Iterator End() const;                       // Iterator to NULL
   Iterator LastNode() const;                  // Iterator to the last node
   bool Empty();

   template <class U>                          // Note the template arg U
   friend ostream& operator <<(ostream& outs, const Simple_List<U>& l);
private:
   node<T>* _head_ptr;

};

template <typename T>
Simple_List<T>::Simple_List() {
    _head_ptr = nullptr;
}

template <typename T>
Simple_List<T>::Simple_List(T item) {
    _head_ptr = new node<T>(item);
}

template <typename T>
Simple_List<T>::~Simple_List() {
    clear_list(_head_ptr);
}

template <typename T>
Simple_List<T>::Simple_List(const Simple_List<T> &copyThis) {
    _head_ptr = copy_list(copyThis._head_ptr);
}

template <typename T>
Simple_List<T>& Simple_List<T>::operator =(const Simple_List<T>& RHS) {
    if (this == &RHS)
        return *this;

    clear_list(_head_ptr);
    _head_ptr = copy_list(RHS._head_ptr);
    return Iterator(_head_ptr);
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::InsertHead(T i) {
    // insert i at the head of list
    return Iterator(insert_head(_head_ptr, i));
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::InsertAfter(T i,
                                                         Iterator iMarker) {
    // insert i after iMarker
    return Iterator(insert_after(_head_ptr, iMarker._ptr, i));
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::InsertBefore(T i,
                                                         Iterator iMarker) {
    // insert i before iMarker
    return Iterator(insert_before(_head_ptr, iMarker._ptr, i));
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::InsertEnd(T i) {
    if(Empty())
        return InsertHead(i);

    Iterator end = Prev(End());
    return InsertAfter(i, end);
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::InsertSorted(T i,
                                                              bool ascending) {
    // insert i. Assume sorted list
    return Iterator(insert_sorted(_head_ptr, i, ascending));
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::InsertSortedAndAdd(T i,
                                                              bool ascending) {
    // insert i. Assume sorted list
    return Iterator(insert_sorted_and_add(_head_ptr, i, ascending));
}

template <typename T>
T Simple_List<T>::Delete(Iterator iMarker) {
    // delete node pointed to by iMarker
    return delete_node(_head_ptr, iMarker._ptr);
}

template <typename T>
T Simple_List<T>::RemoveHead() {
    return delete_node(_head_ptr, _head_ptr);
}

template <typename T>
void Simple_List<T>::Print() const {
    // print the list
    print_list(_head_ptr);
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::Search(const T &key) {
    // return pointer to node containing key. nullptr if not there
    return Iterator(search_list(_head_ptr, key));
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::Prev(Iterator iMarker) {
    // get the previous node to iMarker
    if (iMarker._ptr == _head_ptr)
        return _head_ptr;
    return Iterator(previous_node(_head_ptr, iMarker._ptr));
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::Next(Iterator iMarker) {
    // get the next node to iMarker
    Iterator temp = iMarker.next();
    if(temp._ptr == nullptr)
        return iMarker;
    return Iterator(next_node(_head_ptr, iMarker._ptr));
}

template <typename T>
T& Simple_List<T>::operator[](int index) {
    // return the item at index
    return at(_head_ptr, index);
}
template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::Begin() const {
    // return the head of the list
    return _head_ptr;
}

template <typename T>
typename Simple_List<T>::Iterator Simple_List<T>::End() const {
    // return the tail of the list
    return last_node(_head_ptr);
}

template <typename T>
bool Simple_List<T>::Empty() {
    return empty_list(_head_ptr);
}

template <typename U>
ostream& operator <<(ostream& outs, const Simple_List<U>& l) {
    return print_plain_list(l._head_ptr);
}

#endif // ITERATED_LIST_H
