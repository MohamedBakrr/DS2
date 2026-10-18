//
// Created by Mmoha on 10/18/2026.
//

#ifndef AVLTREE_H
#define AVLTREE_H

#include "linked_queue.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class AVLNode {
public:
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    explicit AVLNode(const T& data) : data(data), left(nullptr), right(nullptr), height(0) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    static int nodeHeight(const AVLNode<T>* node);
    static int getBalance(const AVLNode<T>* node);
    static void updateHeight(AVLNode<T>* node);

    static AVLNode<T>* rotateRight(AVLNode<T>* y);
    static AVLNode<T>* rotateLeft(AVLNode<T>* x);
    static AVLNode<T>* rebalance(AVLNode<T>* node);

    static AVLNode<T>* insertRecursive(AVLNode<T>* node, const T& value, bool& inserted);
    static AVLNode<T>* removeRecursive(AVLNode<T>* node, const T& value, bool& removed);
    static AVLNode<T>* findMinNode(AVLNode<T>* node);
    static AVLNode<T>* findMaxNode(AVLNode<T>* node);
    static AVLNode<T>* searchNode(AVLNode<T>* node, const T& value);
    static void destroyTree(AVLNode<T>* node);

    static int countNodesRecursive(const AVLNode<T>* node);
    static int countLeavesRecursive(const AVLNode<T>* node);
    static int countInternalRecursive(const AVLNode<T>* node);
    static void inorderRecursive(const AVLNode<T>* node);
    static void preorderRecursive(const AVLNode<T>* node);
    static void postorderRecursive(const AVLNode<T>* node);
    static void printLevelRecursive(const AVLNode<T>* node, int level);
    static void printSidewaysRecursive(const AVLNode<T>* node, int depth);
    static void printBalanceFactorsRecursive(const AVLNode<T>* node);

public:
    AVLTree();
    ~AVLTree();

    // AVLTree owns dynamically allocated nodes, so copying is disabled to avoid double deletion.
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    bool insert(const T& value); // false when the value already exists
    bool remove(const T& value); // false when the value does not exist
    bool search(const T& value) const;

    bool isEmpty() const;
    int getHeight() const;       // empty tree = -1, leaf = 0
    int balanceFactor(const T& value) const;
    int countNodes() const;
    int countLeaves() const;
    int countInternal() const;
    T findMin() const;
    T findMax() const;

    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelOrder() const;
    void printLevel(int level) const;
    void printSideways() const;
    void printBalanceFactors() const;
    void clear();
};

#include "AVLTree.tpp"
#endif //AVLTREE_H
