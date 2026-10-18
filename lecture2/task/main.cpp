//
// Created by MohamedBakr on 10/7/2026.
//
#include "BinaryTree.h"
#include "helpers.h"

int main() {
    BinaryTree<int> tree;

    int values[] =  { 10, 20, 2, 3, 15, 60, 30, 1, 39 }; //{10,15,5,20,12,9,2,17,30,3};
    for (int v : values) {
        tree.insert(v);
    }

    helpers::printDivider();
    std::cout << "=== Traversals ===" << std::endl;
    helpers::printSection("Inorder   ", [&]() { tree.inorder(); });
    helpers::printSection("Preorder  ", [&]() { tree.preorder(); });
    helpers::printSection("Postorder ", [&]() { tree.postorder(); });
    helpers::printSection("LevelOrder", [&]() { tree.levelOrder(); });

    helpers::printDivider();
    std::cout << "=== Tree Info ===" << std::endl;
    std::cout << "Height:          " << tree.getHeight() << std::endl;
    std::cout << "Nodes count:     " << tree.countNodes() << std::endl;
    std::cout << "Leaves count:    " << tree.countLeaves() << std::endl;
    std::cout << "Internal nodes:  " << tree.countInternal() << std::endl;
    std::cout << "Min value:       " << tree.findMin() << std::endl;
    std::cout << "Max value:       " << tree.findMax() << std::endl;
    std::cout << "Is empty:        " << (tree.isEmpty() ? "Yes" : "No") << std::endl;

    helpers::printDivider();
    std::cout << "=== Print Levels Separately ===" << std::endl;
    for (int i = 0; i <= tree.getHeight(); i++) {
        std::cout << "Level " << i << ": ";
        tree.printLevel(i);
    }

    helpers::printDivider();
    std::cout << "=== Search ===" << std::endl;
    helpers::printSearchResult(40, tree.search(40));
    helpers::printSearchResult(5, tree.search(5));

    helpers::printDivider();
    std::cout << "=== After Deletion ===" << std::endl;
    tree.remove(10);

    helpers::printSection("Inorder ", [&]() { tree.inorder(); });
    std::cout << "Height:      " << tree.getHeight() << std::endl;
    std::cout << "Nodes count: " << tree.countNodes() << std::endl;

    helpers::printDivider();
    std::cout << "=== After Clear ===" << std::endl;
    tree.clear();
    std::cout << "Is empty: " << (tree.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}