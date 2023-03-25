#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>

// Each node will have  a label (yes/no) and left, middle, right and a parent
template <typename T>
struct Node{
    T label;
    T data;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *middle = nullptr;
    Node *right = nullptr;
    int nodeNum;               // Number visited in preorder
    int nodeLevel;             // Level of the node in the tree
    bool isOpen = true;               // Can more children be added? (Open to add children)
};

template <typename T>
class Tree{
    public:
        // Position of a node in the tree
        class Position{
            private:
                Node<T> *v;
            public:
                Position(Node<T> *_v = NULL){           // Constructor
                    v = _v;
                } 
                T& operator*() { return v->data; }   // Dereference to get data

                // Get left, middle, right child and parent
                Position left() const{ return Position(v->left); }
                Position middle() const{ return Position(v->middle); } 
                Position right() const{ return Position(v->right); }
                Position parent() const { return Position(v->parent); }

                // Get label
                T label() const { return v->label; }

                // is root? is external?
                bool isRoot() const { return v->parent == nullptr; }
                bool isExternal() const {
                    return v->left == nullptr && v->middle == nullptr && v->right == nullptr;
                }

                // Close node
                void close() { v->isOpen = false;}

                friend class Tree;
        };

        typedef std::vector<Position> PositionList;    // List of positions (stored as a vector)

        Tree();                                      // Constructor
        int size() const;                            // Number of node
        bool empty() const;                          // Is tree empty?
        Position root() const;                       // Get root position
        Node<T>* rootNode() const;                    // Get root node
        void addRoot(const T _data , const T _label);                 // Add root to tree 
        
        Position addLeft(const Position &p, const T _data , const T _label , const int _nodeNum);       // Add a node to the left of p, returns position of added node
        Position addMiddle(const Position &p, const T _data , const T _label, const int _nodeNum);     // Add a node to the middle of p, returns position of added node
        Position addRight(const Position &p, const T _data , const T _label, const int _nodeNum);      // Add a node  to the Right of p, returns position of added node

        PositionList positions() const; // List of nodes
        void printPositionList() const; // Prints details of each node in preorder format

        // Expand external node
        void expandExternal( const Position &p);

        // Preorder Traversal
        void preorder(Node<T> *v, PositionList &pl) const;

        /* Functions needed to convert the textfile to a tree*/

            // Given a node, find leftmost open node
            Node<T>* nextOpen(Node<T> *n , bool checkMiddle);

            // Check whether parent node is suitable
            bool checkParent(Node<T> *parentNode , Node<T> *childNode);

            // Add node to tree
            void addToTree(Node<T> *childNode , Node<T> *rootNode);

    private:
        Node<T> *_root; // Pointer to root
        int n; // Number of nodes
};

// Constructor
template <typename T>
Tree<T>::Tree() : _root(nullptr) , n(0) {}

// Number of nodes
template <typename T>
int Tree<T>::size() const{
    return n;
}

// Is tree empty?
template <typename T>
bool Tree<T>::empty() const{
    return size() == 0;
}

// Get root position
template <typename T>
typename Tree<T>::Position Tree<T>::root() const{
    return Position(_root);
}

// Get root node
template <typename T>
Node<T>* Tree<T>::rootNode() const{
    return _root;
}


// Add root to empty tree
template <typename T>
void Tree<T>::addRoot(const T _data , const T _label) {
    _root = new Node<T>;
    _root->data = _data;
    _root->label = _label;
    _root->nodeNum = 1;
    _root->nodeLevel = 0;
    n += 1;
}


// Add node w to the left of p
template <typename T>
typename Tree<T>::Position Tree<T>::addLeft( const Position &p , const T _data , const T _label , const int _nodeNum){
    Node<T> *v = p.v;

    v->left = new Node<T>;
    v->left->data = _data;
    v->left->label = _label;
    v->left->nodeNum = _nodeNum;
    v->left->parent = v;
    v->left->nodeLevel = v->nodeLevel + 1;

    n++;

    return Position(v->left);
}

// Add node w to the middle of p
template <typename T>
typename Tree<T>::Position Tree<T>::addMiddle( const Position &p ,  const T _data , const T _label , const int _nodeNum){
    Node<T> *v = p.v;

    v->middle = new Node<T>;
    v->middle->data = _data;
    v->middle->label = _label;
    v->middle->nodeNum = _nodeNum;
    v->middle->parent = v;
    v->middle->nodeLevel = v->nodeLevel + 1;

    n++;

    return Position(v->middle);
}

// Add node w to the right of p
template <typename T>
typename Tree<T>::Position Tree<T>::addRight( const Position &p ,  const T _data , const T _label , const int _nodeNum){
    Node<T> *v = p.v;

    v->right = new Node<T>;
    v->right->data = _data;
    v->right->label = _label;
    v->right->nodeNum = _nodeNum;
    v->right->parent = v;
    v->right->nodeLevel = v->nodeLevel + 1;

    n++;

    return Position(v->right);
}

// List of all Nodes
template <typename T>
typename Tree<T>::PositionList Tree<T>::positions() const{
    PositionList pl;
    preorder(_root,pl);
    return pl;
}

// Prints details of each node in preorder format
template <typename T>
void Tree<T>::printPositionList() const{
    PositionList pl = positions();
    for (int i=0; i<pl.size(); i++){
        Position p = pl[i];
        Node<T> *n = p.v;
        std::cout << n->nodeLevel << "  " << n->nodeNum << "  " << n->label << "   " << n->data << "\n";
    }
}

// Preorder traversal
template <typename T>
void Tree<T>::preorder(Node<T> *v, PositionList &pl) const{
    pl.push_back(Position(v));

    // Traverse Left subtree
    if (v->left != nullptr){
        preorder(v->left,pl);
    }

    // Traverse Middle subtree
    if (v->middle != nullptr){
        preorder(v->middle,pl);
    }

    // Traverse Right subtree
    if (v->right != nullptr){
        preorder(v->right,pl);
    }

    return;
}

// Expand external node
template <typename T>
void Tree<T>::expandExternal(const Position &p){
    Node<T> *v = p.v;   // p's node

    v->left = new Node<T>;               // Add left child
    v->left->parent = v;              // v is parent

    v->middle = new Node<T>;               // Add middle child
    v->middle->parent = v;              // v is parent

    v->right = new Node<T>;               // Add right child
    v->right->parent = v;              // v is parent

    n += 3;
}


// Given a node, find leftmost open node
template <typename T>
Node<T>* Tree<T>::nextOpen(Node<T> *n , bool checkMiddle){
    std::cout << "FINDING NEXT OPEN...\n";

    Position p = Position(n);
    if (p.isExternal()){
        std::cout << "External Node\n";
        return n;
    }

    // Check left node
    if (n->left->isOpen){
        return nextOpen(n->left,checkMiddle);
    }


    // Left closed, Check middle node (only if checkMiddle == true)
    if (checkMiddle == true){
        if (n->middle == nullptr){
            return n;
        }else if (n->middle->isOpen){
            return nextOpen(n->middle,checkMiddle);
        }
    }

    // Middle closed OR Left closed
    if (n->right == nullptr){
        return n;
    }else if (n->right->isOpen){
        return nextOpen(n->right,checkMiddle);
    }

    // Error case
    std::cout << "ERROR IN FINDING NEXT OPEN NODE!!\n";
    return nullptr;
}

// Check whether parent node is suitable
template <typename T>
bool Tree<T>::checkParent(Node<T> *parentNode , Node<T> *childNode){

    if (parentNode->nodeLevel != (childNode->nodeLevel - 1)){
        parentNode->isOpen = false;
        return false;
    }

    return true;
}

// Add node to tree
template <typename T>
void Tree<T>::addToTree(Node<T> *childNode, Node<T> *rootNode){
    bool correctParent = false;                  // Flag
    
    Node<T> *parentNode;                     // Store node of parent
    bool checkMiddle;                     
    if (childNode->label == "Sometimes"){   // If middle node should be checked
        checkMiddle = true;
    }else{
        checkMiddle = false;
    }

    // Find correct parent
    while (correctParent == false){
        parentNode = nextOpen(rootNode,checkMiddle);
        correctParent = checkParent(parentNode,childNode);
    }

    Position parentPos = Position(parentNode);

    if (childNode->label == "Yes"){
        addLeft(parentPos,childNode->data,childNode->label,childNode->nodeNum);
        return;
    }

    if (childNode->label == "Sometimes"){
        addMiddle(parentPos,childNode->data,childNode->label,childNode->nodeNum);
        return;
    }

    if (childNode->label == "No"){
        addRight(parentPos,childNode->data,childNode->label,childNode->nodeNum);
        return;
    }

    std::cout << "ERROR WHILE ADDING NODE!!\n";
    return;

}

#endif
