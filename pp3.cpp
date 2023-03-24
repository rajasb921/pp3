#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.h"

int main(){
    Tree<std::string> testTree;
    
    // Creating tree
    testTree.addRoot("Are you nervous?");
    Tree<std::string>::Position l1 = testTree.addLeft(testTree.root(),"Savings","Yes");
    Tree<std::string>::Position r1 = testTree.addRight(testTree.root(),"Will you need money?","No");
    Tree<std::string>::Position l2 = testTree.addLeft(r1,"Money Market","Yes");
    Tree<std::string>::Position r2 = testTree.addRight(r1,"Risks","No");
    Tree<std::string>::Position l3 = testTree.addLeft(r2,"Stocks","Yes");
    Tree<std::string>::Position r3 = testTree.addRight(r2,"Diversify","No");
    
    int size;
    size = testTree.size();
    std::cout << "size: " << size << "\n";
    
    return EXIT_SUCCESS;
}