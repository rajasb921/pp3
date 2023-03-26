#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

// Node object
template <typename T>
struct Node{
    int nodeLevel;                      // Level node is located (0 = root)
    int nodeNum;                        // Number of node when visited in preorder
    T data;                             // Data stored in node
    T label;                            // Label used to reach node (yes,no,sometimes)
    Node* parent;                       // Parent of node (root parent = nullptr)
    std::vector<Node*> childList;       // List of children
};

// Tree class
template <typename T>
class Tree{
    private:
        Node<T> *root;                   // Root
        int n;                           // Size of tree
    public:

        // Position class to keep track of the position of each node in the tree
        class Position{
            private:
                Node<T> *v;              // Node
            public:
                Position(Node<T> *_v = nullptr){         // Constructor
                    v = _v;
                }
                T &operator*() {return v->data;}         // Dereference to get data
                Node<T> *getNode() {return v;}           // Return node

                std::vector<Node<T>*> getChildren() const {return v->childList;}    // Return list of children
                T label() const {return v->label;}                                  // Return label
                bool isRoot() const {return v->parent == nullptr;}                  // is Root?
                bool isExternal() const {return (v->childList.size() == 0);}        // is External?

                friend class Tree;
        };

        typedef std::vector<Position> PositionList;               // List of all positions (stored in preorder)

        // Constructor
        Tree(){
            root = nullptr;
            n = 0;
        }

        // Get size
        int size(){
            return n;
        }

        // is Empty?
        bool isEmpty(){
            return size() == 0;
        }

        // Return position of root
        Position rootPosition() const{
            return Position(root);
        }

        // Return root node
        Node<T>* rootNode() const{
            return root;
        }

        // Add root
        void addRoot(const T _data, const T _label){
            Node <T> *newRoot  = new Node<T>;
            newRoot->data = _data;
            newRoot->label = _label;
            newRoot->nodeLevel = 0;             // Root at level 0
            newRoot->nodeNum = 1;               // Root visited first in preorder
            newRoot->parent = nullptr;          // Root parent is nullptr

            root = newRoot;
            n++;
        }
        
        // Add child, return node of child
        Node<T> *addChild (Node<T>* parentNode, Node<T>* childNode){
            parentNode->childList.push_back(childNode);      // Add childNode to childList 
            childNode->parent = parentNode;                  // Update parent of childNode

            n++;
            return childNode;
        }

        // Preorder traversal
        void preorder(Node<T> *v, PositionList &pl){
            pl.push_back(Position(v));

            if (Position(v).isExternal()){
                return;
            }else{
                for (int i=0; i<v->childList.size(); i++){
                    preorder(v->childList[i],pl);
                }
            }
        }

        // Preorder print
        void preorderPrint(Node<T> *n){
            std::cout << n->nodeLevel << "  " << n->nodeNum << "  " << n->label << "   " << n->data << "\n";

            if (n->childList.size() == 0){
                return;
            }else{
                for (int i=0; i<n->childList.size(); i++){
                    preorderPrint(n->childList[i]);
                }
            }
        }

        // Create positionList
        PositionList positions(){
            PositionList pl;
            preorder(rootNode(),pl);
            return pl;
        }

        // Print details of each node in position list
        void printPositionList(){
            PositionList pl = positions();
            for (int i=0; i<pl.size(); i++){
                Node<T> *n = pl[i].getNode();
                std::cout << n->nodeLevel << "  " << n->nodeNum << "  " << n->label << "   " << n->data << "\n"; 
            }
        }

        // Get list of nodes given a filename
        std::vector<Node<T>*> getNodeList(std::string filename){
            // opening file
            std::ifstream myFile;
            myFile.open(filename);


            // Variables
            std::string levelStr;
            std::string nodeStr;
            std::string label;
            std::string data;
            int numLevel;
            int numNode;

            // Nodelist
            std::vector<Node<std::string>*> NodeList;

            // Add to Nodelist
            std::string line;
            while (std::getline(myFile,line)){
                // To read tab separated values
                std::istringstream tab_string(line);

                std::getline(tab_string,levelStr,'\t');
                numLevel = std::stoi(levelStr);

                std::getline(tab_string,nodeStr,'\t');
                numNode = std::stoi(nodeStr);

                std::getline(tab_string, label, '\t');
                std::getline(tab_string, data, '\n');

                Node<std::string> *n = new Node<std::string>;
                n->data = data;
                n->label = label;
                n->nodeLevel = numLevel;
                n->nodeNum = numNode;

                NodeList.push_back(n);
            }

            return NodeList;
        }

};

#endif