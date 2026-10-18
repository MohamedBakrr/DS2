//
// Created by Mmoha on 10/18/2026.
//
#include "AVLTree.h"
#include <iostream>

int main() {
    AVLTree<int> tree;
    int values[] = {10, 20, 2, 3, 15, 60, 30, 1, 39};

    for (int value : values) {
        if (!tree.insert(value))
            std::cout << "Duplicate ignored: " << value << '\n';
    }

    std::cout << "=== Traversals ===\n";
    std::cout << "Inorder:    "; tree.inorder();
    std::cout << "Preorder:   "; tree.preorder();
    std::cout << "Postorder:  "; tree.postorder();
    std::cout << "Level order:"; tree.levelOrder();

    std::cout << "\n=== Tree information ===\n";
    std::cout << "Height: " << tree.getHeight() << '\n';
    std::cout << "Nodes: " << tree.countNodes() << '\n';
    std::cout << "Leaves: " << tree.countLeaves() << '\n';
    std::cout << "Internal nodes: " << tree.countInternal() << '\n';
    std::cout << "Minimum: " << tree.findMin() << '\n';
    std::cout << "Maximum: " << tree.findMax() << '\n';
    std::cout << "Search 30: " << (tree.search(30) ? "Found" : "Not found") << '\n';

    std::cout << "\n=== Tree by levels ===\n";
    for (int level = 0; level <= tree.getHeight(); ++level) {
        std::cout << "Level " << level << ": ";
        tree.printLevel(level);
    }

    std::cout << "\n=== Sideways tree (includes height and balance factor) ===\n";
    tree.printSideways();

    std::cout << "\n=== Balance factors (inorder) ===\n";
    tree.printBalanceFactors();

    std::cout << "\n=== Remove 10 ===\n";
    std::cout << (tree.remove(10) ? "Removed\n" : "Value not found\n");
    tree.inorder();
    tree.printSideways();

    tree.clear();
    std::cout << "\nAfter clear, empty: " << (tree.isEmpty() ? "Yes" : "No") << '\n';
    return 0;
}
