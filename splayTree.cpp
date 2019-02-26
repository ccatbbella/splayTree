#include "splayTree.h"
using namespace std;


SplayTree::SplayTree(){
    root = NULL;
}


Node* SplayTree::max() const{
	Node* n = root;
	while (n->right != NULL) {
		n = n->right;
	}
	return n;
}


Node* SplayTree::getRoot(){return root;}

bool SplayTree::isLeftChild(Node* child){
    if(child->parent!=NULL){  //child is not root
        return child->parent->left == child;
    }else{
        return false;
    }
}
bool SplayTree::isRightChild(Node* child){
    if(child->parent!=NULL){
        return child->parent->right == child;
    }else{
        return false;
    }
}
bool SplayTree::isRoot(Node *n)
{
    return n != NULL && n->parent == NULL;
}

bool SplayTree::isLeaf(Node *n)
{
    return n != NULL && n->left == NULL && n->right == NULL;
}


void SplayTree::rotateRight(Node*xp){
    //rotate the edge between xp and its parent to the right
    Node* xpParent = xp->parent;
    xpParent->left = xp->right;
    if(xp->right != NULL){
        xp->right->parent = xpParent;
    }
    xp->right = xpParent;
    xp->parent = xpParent->parent;
    if(xpParent->parent!=NULL && xpParent->parent->left == xpParent){
        xpParent->parent->left = xp;
    }
    else if(xpParent->parent!=NULL && xpParent->parent->right == xpParent){
        xpParent->parent->right = xp;
    }
    xpParent->parent = xp;
    if(isRoot(xp)){root = xp;}
}
void SplayTree::rotateLeft(Node*xp){
    //rotate the edge between xp and its parent to the left
    Node* xpParent = xp->parent;
    xpParent->right = xp->left;
    if(xp->left != NULL){
        xp->left->parent = xpParent;
    }
    xp->left = xpParent;
    xp->parent = xpParent->parent;
    if(xpParent->parent!=NULL && xpParent->parent->left == xpParent){
        xpParent->parent->left = xp;
    }
    else if(xpParent->parent!=NULL && xpParent->parent->right == xpParent){
        xpParent->parent->right = xp;
    }
    xpParent->parent = xp;
    if(isRoot(xp)){root = xp;}
}


void SplayTree::splay(Node* n){//splay the node n is pointing to
    if(isRoot(n)){ return; }
    //case Zig, root is parent of &n
    if(isRoot(n->parent)){
        if(isLeftChild(n)) { rotateRight(n); }
        if(isRightChild(n)) { rotateLeft(n); }
    }
    else{
        //case Zig-zig
        if(isLeftChild(n) && isLeftChild(n->parent)) {
            rotateRight(n->parent);
            rotateRight(n);
        }
        if(isRightChild(n) && isRightChild(n->parent)) {
            rotateLeft(n->parent);
            rotateLeft(n);
        }

        //case Zig-zag
        if(isLeftChild(n) && isRightChild(n->parent)) {
            rotateRight(n);
            rotateLeft(n);
        }
        if(isRightChild(n) && isLeftChild(n->parent)) {
            rotateLeft(n);
            rotateRight(n);
        }
    }
    splay(n);
}

void SplayTree::insert(int i)
{
	Node* n = new Node(i);
    // handle empty tree
    if (this->root == NULL)
    {
        this->root = n;
		cout << "item " << i << " inserted" << endl;
        return;
    }
	access(i, root);
	if (this->root->data == i) {
		cout << "item " << i << " not inserted; already present" << endl;
		return;
	}
	else {
		vector<SplayTree> trees = split(i);
		n->left = trees.at(0).getRoot();
		if (n->left != NULL) {
			n->left->parent = n;
		}
		n->right = trees.at(1).getRoot();
		if (n->right != NULL) {
			n->right->parent = n;
		}
		setRoot(n);
		cout << "item " << i << " inserted" << endl;
	}
}



void SplayTree::printPreOrder() const
{
    printPreOrder(root);
}
void SplayTree::printPreOrder(Node *n) const
{

    if (n)
    {
        cout << n->data << " ";
        printPreOrder(n->left);
        
        printPreOrder(n->right);
    }
}

Node* SplayTree::access(int i, Node* n){ //access i in tree whose root is n, n cannot be NULL
	if(n->data == i){
        splay(n);
        return n;
    }
    else{
        if(isLeaf(n)){
            splay(n);
            return NULL;
        }
        else{
            if(n->data < i){
				if (n->right != NULL) { return access(i, n->right); }
				else{
					splay(n);
					return NULL;
				}
            }
			else {
				if (n->left != NULL) { return access(i, n->left); }
				else {
					splay(n);
					return NULL;
				}

			}
          
        }
    }
}

void SplayTree::find(int i){
    if(access(i, root) != NULL){
        cout << "item " << i << " found" << endl;
    }
    else{
        cout << "item " << i << " not found" << endl;
    }
}
void SplayTree::setRoot(Node* n) { root = n; }
SplayTree join(SplayTree t1, SplayTree t2) {
	SplayTree result;
	if( t1.getRoot() == NULL && t2.getRoot() == NULL){ return result; }
	if( t1.getRoot() == NULL && t2.getRoot() != NULL){ return t2; }
	if( t1.getRoot() != NULL && t2.getRoot() == NULL){ return t1; }
	t1.access(t1.max()->data, t1.getRoot());

	t1.getRoot()->right = t2.getRoot();
	t2.getRoot()->parent = t1.getRoot();
	result.setRoot(t1.getRoot());
	return result;
}

void SplayTree::deleteTree(int i){
	if(root == NULL) return;
	if(access(i, root) == NULL){
		cout << "item " << i << " not deleted; not present" << endl;
	}
	else{
		SplayTree t1;
		t1.setRoot(this->root->left);
		if (this->root->left != NULL) {
			this->root->left->parent = NULL;
			this->root->left = NULL;
		}
		
		SplayTree t2;
		t2.setRoot(this->root->right);
		if (this->root->right != NULL) {
			this->root->right->parent = NULL;
			this->root->right = NULL;
		}
		
		SplayTree t3 = join(t1, t2);
		delete root;
		root = t3.getRoot();
		cout << "item " << i << " deleted" << endl;
	}
}
vector<SplayTree> SplayTree::split(int i) {
	SplayTree t1; SplayTree t2;
	vector<SplayTree> result;
	
	if (root == NULL) {
		result.push_back(t1);
		result.push_back(t2);
		return result;
	}
	access(i, root);
	if(root->data > i){ //break left child link
		t1.setRoot(this->root->left);
		if (this->root->left != NULL) {
			this->root->left->parent = NULL;
			this->root->left = NULL;
		}
		t2.setRoot(this->root);
	}
	else { //break right child link
		t1.setRoot(this->root);
		t2.setRoot(this->root->right);
		if (this->root->right != NULL) {
			this->root->right->parent = NULL;
			this->root->right = NULL;
		}
	}
	result.push_back(t1);
	result.push_back(t2);
	return result;
}