struct Node{
        int data;
        Node* left;
        Node* right;
}

class SplayTree{
        public:
                Node* access(int i);
                SplayTree join(SplayTree tree1, SplayTree tree2);
};