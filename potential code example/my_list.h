#ifndef MY_LIST_H
#define MY_LIST_H

#include <iostream>
#include <assert.h>
#include "node.h"

using namespace std;

template<typename T>
node<T>* insert_head(node<T>* &head_ptr, const T& item);

template <typename T>
node<T>* search_list(node<T>* head,              // return ptr to key or NULL
                    T key);

template <typename T>
node<T>* insert_after(node<T>* &head, node<T>    // insert after ptr
                      *afterThis, T item);

template <typename T>
node<T>* insert_before(node<T>* &head,           // insert before ptr
                       node<T>* beforeThis,
                       T insertThis);

template <typename T>
node<T>* previous_node(node<T>* head,            // ptr to previous node
                      node<T>* given_node);

template <typename T>
node<T>* next_node(node<T>* &head, node<T>* given_node); // ptr to next node

template <typename T>
T delete_node(node<T>*&head,               // delete, return item
              node<T>* deleteThis);

template <typename T>
T delete_head(node<T>*&head);

template <typename T>
node<T>* copy_list(node<T>* head);         // duplicate the list...

template <typename T>
void clear_list(node<T>*& head);           // delete all the nodes

template <typename T>
T& at(node<T>* head, int pos);             // _item at this position

template <typename T>
node<T>* insert_sorted(node<T>* &head, T item, bool ascending); // insert
template <typename T>
node<T>* insert_sorted_and_add(node<T>* &head, T item, bool ascending);

template <typename T>
node<T>* where_this_goes(node<T>* head,     // node after which this item goes
                        T item, bool ascending);

template <typename T>
node<T>* last_node(node<T>* head);          // last node in the list

template <typename T>
bool empty_list(node<T>* head);

template<typename T>
ostream& print_list(node<T>* head_ptr, ostream& outs = cout);

template<typename T>
ostream& print_plain_list(node<T>* head_ptr, ostream& outs = cout);

//============================================//

template<typename T>
node<T>* insert_head(node<T>* &head_ptr, const T& item){
    node<T>* temp = new node<T>(item);  // create a new node
    temp->_next = head_ptr; // point this new node to where head is pointing to
    head_ptr = temp;    // point head to this new node
    return head_ptr;
}

template <typename T>
node<T>* insert_before(node<T>* &head, node<T>* beforeThis,
                       T insertThis) {  // insert before ptr
    assert(head != nullptr);
    assert(beforeThis != nullptr);

    node<T>* temp = previous_node(head, beforeThis);
    // sets temp to the previous node
    temp = insert_after(head, temp, insertThis);
    // insert after the previous node
    return temp;
}


template <typename T>
node<T>* insert_after(node<T>* &head, node<T> *afterThis, T item) {
    // insert after ptr
    assert(afterThis != nullptr);

    node<T>* temp = new node<T> (item, afterThis->_next);
    // creates a new node and sets it's next to afterThis next
    afterThis = previous_node(head, afterThis->_next);
    // checks that afterThis exists within the list given
    afterThis->_next = temp;
    // sets afterThis next to temp
    return temp;
}

template <typename T>
node<T>* search_list(node<T>* head, T key) { //return ptr to key or NULL
    for(node<T> *search = head; search != nullptr; search = search->_next) {
        // searches for value given
        if (search->_item == key)
            return(search);  // returns the address where the element was found
    }
    return nullptr;          // returns a null pointer if value is not found

}

template <typename T>
node<T>* previous_node(node<T>* head, node<T>* given_node) {
    // ptr to previous node
    assert(head != nullptr);

    if (given_node == head) // there is no previous
        return nullptr;

    node<T> *temp_walker = head;

    while (temp_walker != nullptr && temp_walker->_next != given_node)
        // goes through the list until temp_walker->_next == given_node
        temp_walker = temp_walker->_next;

    return temp_walker;
}

template <typename T>
node<T>* next_node(node<T>* &head, node<T>* given_node) {   //ptr to next node
    assert(given_node != nullptr);
    previous_node(head, given_node->_next);
    // checks if given_node exists within the linked list otherwise asserts
    return given_node->_next;
}

template <typename T>
T delete_node(node<T>* &head, node<T>* deleteThis) { //delete, return item
    assert(deleteThis != nullptr);

    node<T> *previous;
    T temp_item = deleteThis->_item;

    if (head == deleteThis) {
        return delete_head(head);
    }

    previous = previous_node(head, deleteThis); // grabs the previous node
    previous->_next = deleteThis->_next;  // removes deleteThis from the list
    delete deleteThis;
    return(temp_item);
}

template <typename T>
T delete_head(node<T>*&head) {
    node<T>* deleteThis = head;
    T temp_item = deleteThis->_item;
    head = deleteThis->_next;   // changes the head to the next node
    delete deleteThis;          // deletes the former head
    return(temp_item);
}

template <typename T>
node<T>* copy_list(node<T>* head) {        //duplicate the list...
    node<T> *new_head = new node<T>(head->_item), *next;
    // creates the new head with the item of the orginnial
    node<T> *previous = new_head;

    for (node<T>* w = head->_next; w != nullptr; w = w->_next){
        next = new node<T>(w->_item);
        // creates the next new node with the item of the original
        previous ->_next = next;    // sets the previous _next to next
        previous = next;    // sets previous to next to move along the new list
    }
    return new_head;
}

template <typename T>
void clear_list(node<T>* &head) {           // delete all the nodes
    while (head != nullptr)
        delete_node(head, head);
        // deletes each node until the list is empty
}

template <typename T>
T& at(node<T>* head, int pos) {            // _item at this position
    node<T> *temp = head;
    int i = 0;

    while (i < pos) {   // goes to the index specified
        assert(temp != nullptr);
        temp = temp ->_next;
        i++;
    }
    return temp ->_item;
}

template <typename T>
node<T>* insert_sorted(node<T>* &head, T item, bool ascending) {
    node<T> *after_this = where_this_goes(head, item, ascending);
    // determines after which node the item belongs
    if(after_this == nullptr)   // if the node belongs at the beginning
        return insert_head(head, item);

    return insert_after(head, after_this, item);  // inserts into the list
}

template <typename T>
node<T>* insert_sorted_and_add(node<T>* &head, T item, bool ascending) {
    node<T>* location = search_list(head, item);
    if (location == nullptr)
        return insert_sorted(head, item, ascending);
    location->_item = location->_item + item;
    return location;
}

template <typename T>
node<T>* where_this_goes(node<T>* head,     //node after which this item goes
                       T item, bool ascending){
    node<T> *before = head, *after;

    if (head == nullptr || (ascending && item <= head->_item) ||
        (!ascending && item >= head->_item))
        // item belongs at the head or list is empty
        return nullptr;

        for (after = head->_next; after != nullptr; after = after->_next,
             before = before->_next) {

            if ((item >= before->_item && item < after->_item) ||
                (item <= before->_item && item > after->_item))
                // item is between two values
                return before;
        }

        return before;  // item belongs at the end

}

template <typename T>
node<T>* last_node(node<T>* head) {         //last node in the list
    assert(head != nullptr);

    node<T> *before = head, *after = head ->_next;

    while (after != nullptr){   //goes through the list till after == nullptr
        after = after->_next;
        before = before->_next;
    }
    return after;
}

template <typename T>
bool empty_list(node<T>* head) {
    if (head == nullptr)
        return true;
    return false;
}

template<typename T>
ostream& print_list(node<T>* head_ptr, ostream& outs){
    outs<<"H->";
    for (node<T>* w = head_ptr; w!=nullptr; w = w->_next){
        outs << "[" << *w << "]->";
    }
    outs<<"|||";
    return outs;
}

template<typename T>
ostream& print_plain_list(node<T>* head_ptr, ostream& outs){
    for (node<T>* w = head_ptr; w!=nullptr; w = w->_next){
        outs << *w << " ";
    }
    return outs;
}

#endif // MY_LIST_H
