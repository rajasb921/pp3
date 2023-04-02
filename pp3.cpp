#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.h"

int main(){
    // Create tree
    std::string filename;
    std::cout << "\nEnter the filename of the tree: ";
    std::cin >> filename;
    Tree<std::string> tree = tree.createTree(filename);
    std::cout << "Tree created!\n";


    // Create output file

    
    // Interact with tree;
    int MAX_N  = tree.size();
    std::cout << "-----------------\nEXPLORE THE TREE\n-----------------\n\n";

    bool flag = true;
    std::string option;

    while(flag){
        std::cout << "Which node would you like to explore? (Enter a position as a number or \"exit\" to exit the program):  ";
        std::cin >> option;

        if (option == "exit"){
            std::cout << "Goodbye!\n\n";
            flag = false;
        }else{
            int optionNum = std::stoi(option);
            if (optionNum > MAX_N || optionNum == 0){
                std::cout << "Invalid Input. Please try again.\n\n";
            }else{
                tree.printNode(optionNum);
            }
        }
    }
}
