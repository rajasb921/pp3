#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.h"

int main(){

    // Check size, empty
    Tree<std::string> t;
    std::cout << t.size() << "\n";
    

    // Check add root
    t.addRoot("This is root","");
    std::cout << t.size() << "\n";
    

    // Check add child
    /*
    Node<std::string>* newChild = new Node<std::string>;
    newChild->data = "This is child one";
    newChild->label = "Yes";
    newChild->nodeNum = 2;
    newChild->nodeLevel = 1;
    t.addChild(t.rootNode(),newChild);
    std::cout << t.size() << "\n";
    std::cout << "Parent is: " << newChild->parent->data << "\n";

    // Check position list
    t.printPositionList();
    */

    // Check file to nodelist
    std::vector<Node<std::string>*> nodeList = t.getNodeList("tree-car.txt");
    // Print NodeList
    for (int i=0; i<nodeList.size(); i++){
        std::cout << nodeList[i]->data << "\n";
    }
    std::cout << "\n";
    return EXIT_SUCCESS;
}