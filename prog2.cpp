#include <iostream>
#include <vector>
#include "splayTree.h"
using namespace std;

int main(){
    SplayTree t;
	int firstLine; 
	cin >> firstLine;
	string in; int i;
	while (!cin.eof()) {
		cin >> in;
		cin >> i;
		if (in == "insert") {
			t.insert(i);

		}
		else if (in == "delete") {
			t.deleteTree(i);

		}
		else if (in == "find") {
			t.find(i);

		}
		//else if (in == "stat") t.stat();
	}
    return 0;
}