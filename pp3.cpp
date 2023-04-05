#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "tree.h"

int main()
{
    // Create tree
    std::string filename;
    std::cout << "\nEnter the filename of the tree: ";
    std::cin >> filename;
    Tree<std::string> tree = tree.createTree(filename);
    std::cout << "Tree created!\n\n";

    // Write + Output Formatted Tree Preorder
    std::ofstream Ofile;
    Ofile.open("about_tree.txt");

    std::string tempBuff = tree.preorderPrintTree(tree.rootNode());
    Ofile << tempBuff; //Ofile
    std::cout << tempBuff; //cout

    // Tree Properties: cout 
    std::cout << "\n-----------------\nTree Properties\n-----------------\n\n";
    std::cout << "Root: " << tree.rootNode()->data << std::endl;
    std::cout << "Number of internal nodes: " << tree.numInternalNodes() << std::endl;
    std::cout << "Number of external nodes: " << tree.numExternalNodes() << std::endl;
    std::cout << "Tree height: " << tree.height() << std::endl;

    std::cout << "\nInternal Nodes: \n" << tree.internalNodes();

    std::cout << "\nExternal Nodes: \n" << tree.externalNodes();

    // Tree Properties: Ofile
    Ofile << "\n-----------------\nTree Properties\n-----------------\n\n";
    Ofile << "Root: " << tree.rootNode()->data << std::endl;
    Ofile << "Number of internal nodes: " << tree.numInternalNodes() << std::endl;
    Ofile << "Number of external nodes: " << tree.numExternalNodes() << std::endl;   
    Ofile << "Tree height: " << tree.height() << std::endl;                          

    Ofile << "\nInternal Nodes: \n" << tree.internalNodes();

    Ofile << "\nExternal Nodes: \n" << tree.externalNodes();
    
    // Binary Tree Properties: cout 
    std::cout << "\n-----------------\nBinary Tree Properties\n-----------------\n\n";

    std::cout << "Binary Tree: ";
    if (tree.isBinary()){
        std::cout << "Yes\n";
        //Proper?
        std::cout << "Proper Tree: ";
        if (tree.isProper()){
            std::cout << "Yes\n";
        }else{
            std::cout << "No\n";
        }
        //Perfect? 
        std::cout << "Perfect Tree: ";
        if (tree.isPerfect()){
            std::cout << "Yes\n";
        }else{
            std::cout << "No\n";
        }
        //Balanced?
        std::cout << "Balanced Tree: ";
        if (tree.isBalanced(tree.rootNode())){
            std::cout << "Yes\n";
        }else{
            std::cout << "No\n";
        }

    }else{
        std::cout << "No\n";
    }

    // Binary Tree Properties: Ofile
    Ofile << "\n-----------------\nBinary Tree Properties\n-----------------\n\n";

    Ofile << "Binary Tree: ";
    if (tree.isBinary()){
        Ofile << "Yes\n";
        //Proper?
        Ofile << "Proper Tree: ";
        if (tree.isProper()){
            Ofile << "Yes\n";
        }else{
            Ofile << "No\n";
        }
        //Perfect? 
        Ofile << "Perfect Tree: ";
        if (tree.isPerfect()){
            Ofile << "Yes\n";
        }else{
            Ofile << "No\n";
        }
        //Balanced?
        Ofile << "Balanced Tree: ";
        if (tree.isBalanced(tree.rootNode())){
            Ofile << "Yes\n";
        }else{
            Ofile << "No\n";
        }

    }else{
        Ofile << "No\n";
    }

    // Interact with tree (Terminal Only)
    size_t MAX_N = tree.size();
    std::cout << "\n-----------------\nEXPLORE THE TREE\n-----------------\n\n";

    bool flag = true;
    std::string option;

    while (flag)
    {
        std::cout << "Which node would you like to explore? (Enter a position as a number or \"exit\" to exit the program):  ";
        std::cin >> option;

        if (option == "exit")
        {
            std::cout << "Goodbye!\n\n";
            flag = false;
        }
        else
        {
            size_t optionNum = std::stoul(option);
            if (optionNum > MAX_N || optionNum == 0)
            {
                std::cout << "Invalid Input. Please try again.\n\n";
            }
            else
            {
                tree.printNode(optionNum);
            }
        }
    }
    
    Ofile.close();
    return 0;
}
