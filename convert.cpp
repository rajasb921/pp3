#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "tree.h"

std::vector<Node<std::string>*> getNodeList(std::string filename){
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



int main(){
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    std::vector<Node<std::string>*> NodeList = getNodeList(filename);

    // Print NodeList
    for (int i=0; i<NodeList.size(); i++){
        std::cout << NodeList[i]->data << "\n";
    }
    std::cout << "\n";

    // Creating tree
    Tree<std::string> testTree;
    testTree.addRoot(NodeList[0]->data,NodeList[0]->label);

    for(int i=1; i<NodeList.size(); i++){

        Node<std::string> *childNode = NodeList[i];
        std::cout << "Child: " << childNode->data << "\n";
        Node<std::string> *parentNode;
        Tree<std::string>::Position parentPos;
        bool parentCheck = false;

        while (parentCheck == false){
        // Check nextOpen()
        parentNode = testTree.nextOpen(testTree.rootNode(),false);
        std::cout << "Next open node: (" << parentNode->nodeLevel << "," << parentNode->nodeNum << ")" << "\n";

        // Check checkParent()
        parentCheck = testTree.checkParent(parentNode,childNode);
        std::cout << "Valid parent: " << parentCheck << "\n";
        }

        
        // Parent,child details
        std::cout << "Parent: " << parentNode->data << "\n";
        

        //Convert to position
        parentPos = Tree<std::string>::Position(parentNode);
        std::cout << "Conversion successful\n";


        // Adding
        if (childNode->label == "Yes"){
        std::cout << "Adding Left...\n";
        testTree.addLeft(parentPos,childNode->data,childNode->label,childNode->nodeNum);
        std::cout << "ADD SUCCESS\n\n";
        continue;
        }

        if (childNode->label == "Sometimes"){
        std::cout << "Adding Middle...\n";
        testTree.addMiddle(parentPos,childNode->data,childNode->label,childNode->nodeNum);
        std::cout << "ADD SUCCESS\n";
        continue;
        }

        if (childNode->label == "No"){
        std::cout << "Adding Right...\n";
        testTree.addRight(parentPos,childNode->data,childNode->label,childNode->nodeNum);
        std::cout << "ADD SUCCESS\n";
        continue;
        }
        
        
    }

    
    int size;
    size = testTree.size();
    std::cout << "size: " << size << "\n";

    testTree.printPositionList();

    return EXIT_SUCCESS;
}

/*

// Checks
    Node<std::string> *testNode;
    bool testCheck;

    // Check nextOpen()
    testNode = testTree.nextOpen(testTree.rootNode(),false);
    std::cout << testNode->data << "\n";

    // Check checkParent()
    testCheck = testTree.checkParent(testNode,NodeList[1]);
    std::cout << testCheck << "\n";

    // Check addToTree()
    testTree.addToTree(NodeList[1],testTree.rootNode());
    int size;
    size = testTree.size();
    std::cout << "Size: " << size << "\n";


*/