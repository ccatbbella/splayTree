#include <iostream>
#include "splayTree.h"
using namespace std;

int main(){
    SplayTree t1;
    
    t1.insert(5);
   
    t1.insert(3);
    t1.insert(12);
    t1.insert(7);
    t1.insert(9);
    t1.insert(40);
    t1.insert(32);
    t1.printPreOrder();
    Node* root = t1.getRoot();
    cout << "root's value is " << root->data << endl;
    t1.deleteTree(5);
    t1.printPreOrder();
   
    root = t1.getRoot();
    cout << "root's value is " << root->data << endl;
    return 0;
}