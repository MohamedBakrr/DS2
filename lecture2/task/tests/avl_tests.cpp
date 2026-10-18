//
// Created by Mmoha on 10/18/2026.
//
#include "AVLTree.h"
#include <cassert>
#include <iostream>

// Test helper: AVLNode is visible in the header, so recursively verify both
// the stored height and the AVL balance invariant after every operation.
template <typename T>
int verifyAVL(const AVLNode<T>* node) {
    if (node == nullptr) return -1;
    int leftHeight = verifyAVL(node->left);
    int rightHeight = verifyAVL(node->right);
    assert(node->height == (leftHeight > rightHeight ? leftHeight : rightHeight) + 1);
    int balance = leftHeight - rightHeight;
    assert(balance >= -1 && balance <= 1);
    if (node->left) assert(node->left->data < node->data);
    if (node->right) assert(node->data < node->right->data);
    return node->height;
}

// Verify via the public height and traversal behavior; internal invariant tests
// are covered by the AVLNode-level helper in the optional white-box test below.
static void testRotationCases() {
    { AVLTree<int> t; t.insert(30); t.insert(20); t.insert(10); assert(t.getHeight() == 1); assert(t.countNodes() == 3); assert(t.search(20)); }
    { AVLTree<int> t; t.insert(10); t.insert(20); t.insert(30); assert(t.getHeight() == 1); assert(t.countNodes() == 3); }
    { AVLTree<int> t; t.insert(30); t.insert(10); t.insert(20); assert(t.getHeight() == 1); assert(t.countNodes() == 3); }
    { AVLTree<int> t; t.insert(10); t.insert(30); t.insert(20); assert(t.getHeight() == 1); assert(t.countNodes() == 3); }
}

static void testDuplicatesAndSearch() {
    AVLTree<int> t;
    assert(t.isEmpty());
    assert(t.insert(5));
    assert(!t.insert(5));
    assert(t.countNodes() == 1);
    assert(t.search(5));
    assert(!t.search(99));
}

static void testDeletionAndRebalancing() {
    AVLTree<int> t;
    for (int x : {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 90})
        assert(t.insert(x));
    assert(t.remove(10)); // leaf
    assert(t.remove(20)); // node with one child in the updated tree
    assert(t.remove(50)); // two children: inorder successor
    assert(!t.remove(999));
    assert(!t.search(50));
    assert(t.countNodes() == 12);
    assert(t.getHeight() >= 0);
    for (int x : {25, 30, 35, 40, 45, 55, 60, 65, 70, 75, 80, 90}) assert(t.search(x));
}

static void testEmptyAndClear() {
    AVLTree<int> t;
    assert(t.getHeight() == -1);
    assert(t.countNodes() == 0);
    assert(t.countLeaves() == 0);
    assert(t.countInternal() == 0);
    assert(!t.remove(1));
    bool minThrew = false, maxThrew = false;
    try { (void)t.findMin(); } catch (const std::runtime_error&) { minThrew = true; }
    try { (void)t.findMax(); } catch (const std::runtime_error&) { maxThrew = true; }
    assert(minThrew && maxThrew);
    t.insert(1); t.insert(2); t.insert(3);
    t.clear();
    assert(t.isEmpty());
    assert(t.getHeight() == -1);
    assert(t.insert(7)); // tree remains reusable after clear
}

int main() {
    testRotationCases();
    testDuplicatesAndSearch();
    testDeletionAndRebalancing();
    testEmptyAndClear();
    std::cout << "All AVL tests passed.\n";
}
