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
        Node* access(int i, Node* root);
        void find(int i);
        void deleteTree(int i);
        bool isRoot(Node* n);
        bool isLeaf(Node *n);
        SplayTree();
        void splay(Node* n);
        Node* getRoot();
     
        void insert(int vi);
        void printPreOrder() const;
        void printPreOrder(Node *n) const;
		Node* max() const;
		void setRoot(Node* n);
		std::vector<SplayTree> split(int i);
private:
        void rotateLeft(Node*xp);
        void rotateRight(Node*xp);
        bool isLeftChild(Node* child); //!child cant be NULL
        bool isRightChild(Node* child);
        Node* root;

};

SplayTree join(SplayTree t1, SplayTree t2);
#endif