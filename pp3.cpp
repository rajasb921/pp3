#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.h"

int main(){

    // Check size, empty
    Tree<std::string> t;
    std::cout << t.size() << "\n";
    
    /*
    // Check add root
    t.addRoot("This is root","");
    std::cout << t.size() << "\n";
    */

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
    std::vector<Node<std::string>*> nodeList = t.getNodeList("tree-investment.txt");

    // Check addChild and positions() using nodes from nodelist
    t.addRoot(nodeList[0]->data,nodeList[0]->label);
    Node<std::string> *l1 = t.addChild(t.rootNode(),nodeList[1]);
    Node<std::string> *r1 = t.addChild(t.rootNode(),nodeList[2]);
    Node<std::string> *l2 = t.addChild(r1,nodeList[3]);
    Node<std::string> *r2 = t.addChild(r1,nodeList[4]);
    Node<std::string> *l3 = t.addChild(r2,nodeList[5]);
    Node<std::string> *r3 = t.addChild(r2,nodeList[6]);

    std::cout << t.size() <<"\n\n";
    /*
    t.preorderPrint(t.rootNode());
    */
    t.positions();
    t.printPositionList();
    return EXIT_SUCCESS;
}