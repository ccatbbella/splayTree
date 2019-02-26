#include "splayTree.h"
using namespace std;

int main(){
    SplayTree t;
	int firstLine; 
	cin >> firstLine;
	string op; int i; // op = operation, i = int value
	while (!cin.eof()) {
		cin >> op;
		cin >> i;
		if (op == "insert") t.insert(i);
		else if (op == "delete") t.deleteTree(i);
		else if (op == "find") t.find(i);
		else if (op == "print") t.print();
	}
    return 0;
}