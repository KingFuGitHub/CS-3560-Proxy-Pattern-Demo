#include <iostream>
#include <time.h>
#include "iterated_application.h"

using namespace std;

void menu(char command, Simple_List<int>& l,
          Simple_List<int>::Iterator &cursor) {
    int key;
    switch(command) {
    case 'R':
        cursor = l.InsertAfter(rand() % 100, cursor);
     break;

    case 'A':
        cout << "key: ";
        cin >> key;
        cout << endl;
        cursor = l.InsertAfter(key, cursor);
     break;

    case 'B':
        cout << "key: ";
        cin >> key;
        cout << endl;
        cursor = l.InsertBefore(key, cursor);
     break;

    case 'D':
        l.Delete(cursor);
        cursor = l.Begin();
     break;

    case 'S':
        cout << "key: ";
        cin >> key;
        cout << endl;
        cursor = l.Search(key);
     break;

    case 'P':
        cursor = l.Prev(cursor);
     break;

    case 'N':
            cursor = l.Next(cursor);
     break;

    case 'H':
        cursor = l.Begin();
     break;

    case 'E':
        cursor = l.End();
     break;

    }
}

void test() {
    srand(time(0));
    char command;
    Simple_List<int> test1(rand() % 100);
    Simple_List<int>::Iterator cursor;

    for (int i = 1; i < 5; i++) {
        cursor = test1.InsertHead(rand() % 100);
    }

    cout << test1 << endl;
    cout << "cursor: " << *cursor << endl;

    do{
        cout << "[R]andom [A]fter  [B]efore [D]elete [S]earch " <<
                "[P]revious  [N] Next  [H]ome  [E]nd  e[x]it" << ":" << endl;
            cin >> command;

            menu(toupper(command), test1, cursor);

            cout << endl << test1 << endl;
            cout << "cursor: " << *cursor << endl;
    }while (toupper(command) != 'X');
}
