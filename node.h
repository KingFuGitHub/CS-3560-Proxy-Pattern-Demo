#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T>
struct node{
  T _item;
  node<T>* _next;

  node(const T& item=T(), node<T>* next = nullptr);

  template <typename U>
  friend ostream& operator<<(ostream& outs, const node<U> n);
};

template <typename T>
node<T>::node(const T& item, node<T>* next): _item(item), _next(next){
    // INTENTIONALLY LEFT BLANK
}

template <typename U>
ostream& operator<<(ostream& outs, const node<U> n) {
    outs << n._item;
    return outs;
}


#endif // NODE_H
