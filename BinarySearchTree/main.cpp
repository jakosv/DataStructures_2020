#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int> bst;
    bst.add(5);
    bst.add(8);
    bst.add(2);
    bst.add(1);
    bst.add(100);
    bst.add(10);
    bst.add(20);
    bst.add(30);
    bst.add(40);
    bst.add(24);
    bst.add(23);
    bst.add(22);
    bst.add(21);
    bst.print();

    std::cout << std::endl;
    BinarySearchTree<int> bst2 = bst;
    bst2.print();
    std::cout << std::endl;
    bst2.clear();

    std::cout << bst.size() << std::endl;
    int value = 20;
    bool found = bst.find(value);
    if (found) {
        std::cout << "Value " << value << " was found" << std::endl;
    }
    else {
        std::cout << "Value " << value << " not found" << std::endl;
    }

    bst.remove(value);
    bst.print();
    std::cout << bst.size() << std::endl;
    found = bst.find(value);
    if (found) {
        std::cout << "Value " << value << " was found" << std::endl;
    }
    else {
        std::cout << "Value " << value << " not found" << std::endl;
    }

    bst2.print();

    return 0;
}
