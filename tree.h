#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>

// Each node will have  a label (yes/no) and left, middle, right and a parent
// Also store whether it is internal node or not
template <typename T>
struct Node{
    T label;
    T data;
    Node *parent;
    Node *left;
    Node *middle;
    Node *right;
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

                // Get left, middle, right child
                Position left() const{ return Position(v->left); }
                Position middle() const{ return Position(v->middle); } 
                Position right() const{ return Position(v->right); }

                // Get label
                T label() const { return v->label; }

                // is root? is external?
                bool isRoot() const { return v->parent == NULL; }
                bool isExternal() const {
                    return v->left == NULL && v->middle == NULL && v->right == NULL;
                }

                friend class Tree;
        };

        typedef std::list<Position> PositionList;    // List of positions (stored in a vector)

        Tree();                                      // Constructor
        int size() const;                            // Number of node
        bool empty() const;                          // Is tree empty?
        Position root() const;                       // Get root
        void addRoot(const T _data);                              // Add root to tree 
        
        Position addLeft(const Position &p, const T _data , const T _label);       // Add a node to the left of p, returns position of added node
        Position addMiddle(const Position &p, const T _data , const T _label);     // Add a node to the middle of p, returns position of added node
        Position addRight(const Position &p, const T _data , const T _label);      // Add a node  to the Right of p, returns position of added node

        PositionList positions() const; // List of nodes

        // Expand external node
        void expandExternal( const Position &p);

        // Preorder Traversal
        void preorder(Node<T> *v, PositionList &pl) const;

    private:
        Node<T> *_root; // Pointer to root
        int n; // Number of nodes
};

// Constructor
template <typename T>
Tree<T>::Tree() : _root(NULL) , n(0) {}

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

// Get root
template <typename T>
typename Tree<T>::Position Tree<T>::root() const{
    return Position(_root);
}

// Add root to empty tree
template <typename T>
void Tree<T>::addRoot(const T _data) {
    _root = new Node<T>;
    _root->data = _data;
    n += 1;
}

// Create a node to be added
template <typename T>
Node<T> Tree<T>::*createNode(const T _data, const T _label){
    Node<T> n = new Node<T>;
    n->data = _data;
    n->label = _label;
    return n;
}

// Add node w to the left of p
template <typename T>
typename Tree<T>::Position Tree<T>::addLeft( const Position &p , const T _data , const T _label){
    Node<T> *v = p.v;

    v->left = new Node<T>;
    v->left->data = _data;
    v->left->label = _label;
    v->left->parent = v;

    n++;

    return Position(v->left);
}

// Add node w to the middle of p
template <typename T>
typename Tree<T>::Position Tree<T>::addMiddle( const Position &p ,  const T _data , const T _label){
    Node<T> *v = p.v;

    v->middle = new Node<T>;
    v->middle->data = _data;
    v->middle->label = _label;
    v->middle->parent = v;

    n++;

    return Position(v->middle);
}

// Add node w to the right of p
template <typename T>
typename Tree<T>::Position Tree<T>::addRight( const Position &p ,  const T _data , const T _label){
    Node<T> *v = p.v;

    v->right = new Node<T>;
    v->right->data = _data;
    v->right->label = _label;
    v->right->parent = v;

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

// Preorder traversal
template <typename T>
void Tree<T>::preorder(Node<T> *v, PositionList &pl) const{
    pl.push_back(Position(v));
    std::cout << v->data << "\n";

    // Traverse Left subtree
    if (v->left != NULL){
        preorder(v->left,pl);
    }

    // Traverse Middle subtree
    if (v->middle != NULL){
        preorder(v->middle,pl);
    }

    // Traverse Right subtree
    if (v->right != NULL){
        preorder(v->right,pl);
    }
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

#endif
