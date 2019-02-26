#include <iostream>
#include <vector>

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

class Node{
public:
        int data;
        Node* left;
        Node* right;
        Node* parent;

        Node(int data){
            left = NULL;
            right = NULL;
            parent = NULL;
            this->data = data;
        }
};

class SplayTree{
public:
        SplayTree();
		void setRoot(Node* n);
        Node* getRoot();
		Node* max() const;
		Node* access(int i, Node* root);
     
        void insert(int vi);
		void find(int i);
		void deleteTree(int i);
		void print() const;
private:
        void rotateLeft(Node*xp);
        void rotateRight(Node*xp);
        bool isLeftChild(Node* child); //!child cant be NULL
        bool isRightChild(Node* child);
		bool isRoot(Node* n);
		bool isLeaf(Node *n);
		

		void splay(Node* n);
		std::vector<SplayTree> split(int i);
		
        
		Node* root;
};

SplayTree join(SplayTree t1, SplayTree t2);

#endif