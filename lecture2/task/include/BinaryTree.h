//
// Created by MohamedBakr on 10/7/2026.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "linked_queue.h"

template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T value);
};

template <typename T>
class BinaryTree {
    Node<T>* root;

    Node<T>* insertRecursive(Node<T>* node, T data);
    Node<T>* searchRecursive(Node<T>* node, T data) const;
    Node<T>* deleteRecursive(Node<T>* node, T data);
    Node<T>* findMinNode(Node<T>* node) const;
    Node<T>* findMaxNode(Node<T>* node) const;
    void destroyTree(Node<T>* node);

    void inorderRecursive(Node<T>* node) const;
    void preorderRecursive(Node<T>* node) const;
    void postorderRecursive(Node<T>* node) const;

    int heightRecursive(Node<T>* node) const;
    int countNodesRecursive(Node<T>* node) const;
    int countLeavesRecursive(Node<T>* node) const;
    int countInternalRecursive(Node<T>* node) const;
    void printLevelRecursive(Node<T>* node, int level) const;

public:
    BinaryTree();
    ~BinaryTree();

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    void insert(T data);
    bool search(T data) const;
    void remove(T data);
    void clear();

    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelOrder() const;

    bool isEmpty() const;
    int getHeight() const;
    int countNodes() const;
    int countLeaves() const;
    int countInternal() const;
    T findMin() const;
    T findMax() const;
    void printLevel(int level) const;
};

#include "BinaryTree.tpp"

#endif //BINARYTREE_H
