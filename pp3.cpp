#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.h"

int main(){

    // Create tree
    Tree<std::string> t;
    std::cout << "Initial tree size: " << t.size() << "\n";
    

    // Create nodeList
    std::vector<Node<std::string>*> nodeList = t.getNodeList("tree-investment.txt");
    
    
    // addtotree
    t.addRoot(nodeList[0]);
    for (int i = 0; i<nodeList.size(); i++){
        Node<std::string>* parent = nodeList[i];
        t.addFromNodeList(parent,nodeList,i);
    }

    // Check tree details
    std::cout << "Tree size now: " <<t.size() <<"\n\n";
    std::cout << "Preorder print:\n ";
    t.positions();
    t.printPositionList();
    std::cout << "\n";
    std::cout << "Tree height: " <<t.height() << "\n";
    std::cout << "Number of internal nodes: " << t.numInternalNodes() <<"\n";
    std::cout << "Number of external nodes: " << t.numExternalNodes() << "\n";
    std::cout << "is Binary?: " << t.isBinary() << "\n";
    std::cout << "is Proper?: " << t.isProper() << "\n";
    std::cout << "is Perfect?: " << t.isPerfect() << "\n";

    return EXIT_SUCCESS;
}
