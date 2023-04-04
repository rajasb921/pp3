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
    std::cout << "Tree created!\n";

    // Create output file + output contents in terminal
    std::ofstream Ofile;
    Ofile.open("about_tree.txt");
    std::string printTree = tree.preorderPrintTree(tree.rootNode());
    Ofile << printTree;
    std::cout << printTree;
    Ofile.close();

    // Tree Properties
    std::cout << "\n-----------------\nTree Properties\n-----------------\n\n";

    // Binary Tree Properties
    std::cout << "\n-----------------\nBinary Tree Properties\n-----------------\n\n";

    // Interact with tree;
    int MAX_N = tree.size();
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
            int optionNum = std::stoi(option);
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

    return 0;
}
