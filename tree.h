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
    bool isAdded = false;               // If node has been added to the tree (NEEDED FOR ADD FUNCTION)
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
                T &operator*() {return v->data;}            // Dereference to get data
                Node<T> *getNode() {return v;}              // Return node
                Node<T> *getParent() {return v->parent;}    // Get parent of node
                std::vector<Node<T>*> getChildren() const {return v->childList;}    // Return list of children
                T label() const {return v->label;}                                  // Return label
                int getNodeLevel() const {return v->nodeLevel;}                     // Return node level
                int getNodeNum() const {return v->nodeNum;}                         // Return node number
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
        void addRoot(Node<T> *newRoot){
            root = newRoot;
            n++;
        }
        

        // Preorder traversal
        void preorder(Node<T> *v, PositionList &pl){
            pl.push_back(Position(v));

            if (Position(v).isExternal()){
                return;
            }else{
                for (size_t i=0; i<v->childList.size(); i++){
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

        // Returns a string with details of each node in position list
        std::string treeDetails(){
            std::string output;
            PositionList pl = positions();
            for (size_t i=0; i<pl.size(); i++){
                Node<T> *n = pl[i].getNode();
                if (i==0){
                    output += n->data += '\n';
                }else{
                    for (int j=0; j < 2*n->nodeLevel; j++){
                        output += "-";
                    }

                    output += "[" + n->label + "] ";
                    output += n->data + "\n"; 
                }
            }

            return output;
        }

        // Get list of nodes given a filename
        std::vector<Node<T>*> getNodeList(std::string filename){
            // opening file
            std::ifstream myFile;
            myFile.open(filename);
            if (!myFile){
                std::cout << "File not found! Terminating!\n\n";
            }

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

        /* --------------------------------------
           ALGORITHM TO CREATE TREE FROM NODELIST
           --------------------------------------*/

        void addFromNodeList (Node<T>* parentNode , std::vector<Node<T>*> nodeList , int j){
            
            // Create possible parents list
            std::vector<Node<T>*> parentList;
            for (size_t i=j; i<nodeList.size(); i++){
                if (nodeList[i]->nodeLevel == parentNode->nodeLevel){
                    parentList.push_back(nodeList[i]);
                }
            }

            // Create possible children list
            std::vector<Node<T>*> childrenList;
            for (size_t i=0; i<nodeList.size(); i++){
                if ((nodeList[i]->nodeLevel == parentNode->nodeLevel+1) && (nodeList[i]->isAdded == false)){
                    childrenList.push_back(nodeList[i]);
                }
            }

            // If only one possible parent
            if (parentList.size() == 1){
                if (childrenList.size() == 0){
                    return;
                }else{
                    for (size_t i = 0; i<childrenList.size(); i++){
                        parentNode->childList.push_back(childrenList[i]);
                        childrenList[i]->parent = parentNode;
                        childrenList[i]->isAdded = true;
                        n++;
                    }
                    return;
                }
            }

            // More than one parent
            int nextParentNum = parentList[1]->nodeNum;
            for (size_t i=0; i<childrenList.size(); i++){
                if (childrenList[i]->nodeNum > nextParentNum){
                    return;
                }else{
                    parentNode->childList.push_back(childrenList[i]);
                    childrenList[i]->parent = parentNode;
                    childrenList[i]->isAdded = true;
                    n++;
                }
            }
        }
        
        // Creating tree
        Tree<T> createTree(std::string filename){
            // Tree
            Tree<T> newTree;
            // Create nodelist
            std::vector<Node<std::string>*> nodeList = getNodeList(filename);

            // addtotree
            newTree.addRoot(nodeList[0]);
            for (int i = 0; i<nodeList.size(); i++){
                Node<std::string>* parent = nodeList[i];
                newTree.addFromNodeList(parent,nodeList,i);
            }

            return newTree;
        }

        // Return content of root
        T rootData() const{
            return root->data;
        }

        // Print contents of a node
        void printNode(int n){
            PositionList pl = positions();
            for (int i=0; i<pl.size(); i++){
                if (pl[i].getNodeNum() == n){
                Node<T> *p = pl[i].getNode();
                
                // Node details
                std::cout << "Node's content: " << p->data << "\n";
                
                // Ancestor details
                if (p->nodeLevel == 0){
                    std::cout << "Ancestor: [NULL] -- Position is root\n";
                }else if (p->nodeLevel == 1){
                    std::cout << "Ancestor: " << p->parent->data << "\n";
                }else{
                    std::cout << "Ancestor: " << p->parent->parent->data << "\n";
                }

                // Descendant details
                if (pl[i].isExternal()){
                    std::cout << "Descendant: [NULL] -- Position has no children\n";
                }else{
                    std::cout << "Descendant: " << p->childList[0]->data << "\n";
                }
                
                // Sibling details
                if (p->nodeLevel == 0){
                    std::cout << "Sibling: [NULL] -- Position has no siblings -- Position is root\n\n";
                    return;
                }
                std::vector<Node<T>*> cl = p->parent->childList;
                for (int j=0; j<cl.size(); j++){
                    if (cl[j]->nodeNum != p->nodeNum){
                        std::cout << "Sibling: " << cl[j]->data << "\n\n";
                        return;
                    }
                }
                std::cout << "Sibling: [NULL] -- Position has no siblings\n\n";
                }
            }
        }

        // Return number of internal nodes
        int numInternalNodes(){
            int count = 0;
            PositionList pl = positions();
            for (size_t i=0; i<pl.size(); i++){
                if(pl[i].isExternal() == false){
                    count++;
                }
            }

            return count;
        }

        // Return number of external nodes
        int numExternalNodes(){
            int count = 0;
            PositionList pl = positions();
            for (size_t i=0; i<pl.size(); i++){
                if(pl[i].isExternal() == true){
                    count++;
                }
            }

            return count;
        }

        // Return tree height
        int height(){
            int maxHeight = 0;
            PositionList pl = positions();
            for (size_t i=0; i<pl.size(); i++){
                if(pl[i].getNodeLevel() > maxHeight){
                    maxHeight = pl[i].getNodeLevel();
                }
            }

            return maxHeight;
        }

        // is Binary?
        bool isBinary(){
            bool binary = true;
            PositionList pl = positions();
            for (size_t i=0; i<pl.size(); i++){
                if (pl[i].getChildren().size() > 2){
                    binary = false;
                    break;
                }
            }
            return binary;
        }


        // is Proper?
        bool isProper(){
            bool proper = true;
            if (isBinary() == false){
                return false;
            }else{
                PositionList pl = positions();
                for (size_t i=0; i<pl.size(); i++){
                    if (pl[i].isExternal()){
                        continue;
                    }
                    
                    if (pl[i].getChildren().size() != 2){
                        proper = false;
                        break;
                    }
                }
            }
            return proper;
        }

        // is Perfect?
        bool isPerfect(){
            bool perfect = true;
            if (isBinary() == false){
                return false;
            }else if (isProper() == false){
                return false;
            }else{
                PositionList pl = positions();
                int height;
                for (size_t i=0; i<pl.size(); i++){
                    if (pl[i].isExternal()){
                        height = pl[i].getNodeLevel();
                        break;
                    }
                }

                for (size_t i=0; i<pl.size(); i++){
                    if (pl[i].isExternal() && pl[i].getNodeLevel() != height){
                        perfect = false;
                        break;
                    }
                }
            }
            return perfect;
        }

        /*---------------
        Is tree balanced?
        -----------------*/

        // Return subtree height (Only for binary trees)
        int subtreeHeight(Node<T> *n){
            if (n->childList.size() == 0){
                return 0;
            }

            if (n->childList.size() == 1){
                return 1 + subtreeHeight(n->childList[0]);
            }

            return 1 + std::max(subtreeHeight(n->childList[0]),subtreeHeight(n->childList[1]));
        }

        // is Balanced?
        bool isBalanced(Node<T>* n) {
            if (n->childList.size() == 0) {
                return true;
            }

            // Calculate subtree heights
            int left_height,right_height;
            if (n->childList.size() == 1){
                int left_height = subtreeHeight(n->childList[0]);
                int right_height = 0;
                // Difference of heights
                return std::abs(left_height - right_height) <= 1;
            }else{
                int left_height = subtreeHeight(n->childList[0]);
                int right_height = subtreeHeight(n->childList[1]);
                
                // Difference of heights
                return std::abs(left_height - right_height) <= 1 && isBalanced(n->childList[0]) && isBalanced(n->childList[1]);
            }

            
        }

};

#endif