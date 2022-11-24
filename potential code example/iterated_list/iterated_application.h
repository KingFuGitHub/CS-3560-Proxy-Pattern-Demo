#ifndef ITERATED_APPLICATION_H
#define ITERATED_APPLICATION_H

#include <iostream>
#include "iterated_list.h"

using namespace std;

void menu(char command, Simple_List<int>& l,
          Simple_List<int>::Iterator &cursor);

void test();

#endif // ITERATED_APPLICATION_H
