//
// Created by MohamedBakr on 10/7/2026.
//

#ifndef BINARYTREE_TPP
#define BINARYTREE_TPP

#include "BinaryTree.h"
#include <iostream>
#include <stdexcept>

template <typename T>
Node<T>::Node(T value) : data(value), left(nullptr), right(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    destroyTree(root);
}

template <typename T>
Node<T>* BinaryTree<T>::insertRecursive(Node<T>* node, T data) {
    if (node == nullptr) {
        return new Node<T>(data);
    }
    if (data < node->data) {
        node->left = insertRecursive(node->left, data);
    } else {
        node->right = insertRecursive(node->right, data);
    }
    return node;
}

template <typename T>
void BinaryTree<T>::insert(T data) {
    root = insertRecursive(root, data);
}

template <typename T>
Node<T>* BinaryTree<T>::searchRecursive(Node<T>* node, T data) const {
    if (node == nullptr || node->data == data) {
        return node;
    }
    if (data < node->data) {
        return searchRecursive(node->left, data);
    }
    return searchRecursive(node->right, data);
}

template <typename T>
bool BinaryTree<T>::search(T data) const {
    return searchRecursive(root, data) != nullptr;
}

template <typename T>
Node<T>* BinaryTree<T>::findMinNode(Node<T>* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T>* BinaryTree<T>::findMaxNode(Node<T>* node) const {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <typename T>
Node<T>* BinaryTree<T>::deleteRecursive(Node<T>* node, T data) {
    if (node == nullptr) return node;

    if (data < node->data) {
        node->left = deleteRecursive(node->left, data);
    } else if (data > node->data) {
        node->right = deleteRecursive(node->right, data);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        if (node->left == nullptr) {
            Node<T>* temp = node->right;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            Node<T>* temp = node->left;
            delete node;
            return temp;
        }
        Node<T>* minRight = findMinNode(node->right);
        node->data = minRight->data;
        node->right = deleteRecursive(node->right, minRight->data);
    }
    return node;
}

template <typename T>
void BinaryTree<T>::remove(T data) {
    root = deleteRecursive(root, data);
}

template <typename T>
void BinaryTree<T>::destroyTree(Node<T>* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template <typename T>
void BinaryTree<T>::clear() {
    destroyTree(root);
    root = nullptr;
}

template <typename T>
void BinaryTree<T>::inorderRecursive(Node<T>* node) const {
    if (node == nullptr) return;
    inorderRecursive(node->left);
    std::cout << node->data << " ";
    inorderRecursive(node->right);
}

template <typename T>
void BinaryTree<T>::inorder() const {
    inorderRecursive(root);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::preorderRecursive(Node<T>* node) const {
    if (node == nullptr) return;
    std::cout << node->data << " ";
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

template <typename T>
void BinaryTree<T>::preorder() const {
    preorderRecursive(root);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::postorderRecursive(Node<T>* node) const {
    if (node == nullptr) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    std::cout << node->data << " ";
}

template <typename T>
void BinaryTree<T>::postorder() const {
    postorderRecursive(root);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::levelOrder() const {
    if (root == nullptr) return;

    LinkedQueue<Node<T>*> queue;
    queue.enqueue(root);

    while (!queue.isEmpty()) {
        Node<T>* current = queue.peek();
        queue.dequeue();
        std::cout << current->data << " ";

        if (current->left != nullptr)  queue.enqueue(current->left);
        if (current->right != nullptr) queue.enqueue(current->right);
    }
    std::cout << std::endl;
}

template <typename T>
bool BinaryTree<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
int BinaryTree<T>::heightRecursive(Node<T>* node) const {
    if (node == nullptr) return -1;
    int leftH = heightRecursive(node->left);
    int rightH = heightRecursive(node->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

template <typename T>
int BinaryTree<T>::getHeight() const {
    return heightRecursive(root);
}

template <typename T>
int BinaryTree<T>::countNodesRecursive(Node<T>* node) const {
    if (node == nullptr) return 0;
    return 1 + countNodesRecursive(node->left) + countNodesRecursive(node->right);
}

template <typename T>
int BinaryTree<T>::countNodes() const {
    return countNodesRecursive(root);
}

template <typename T>
int BinaryTree<T>::countLeavesRecursive(Node<T>* node) const {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 1;
    return countLeavesRecursive(node->left) + countLeavesRecursive(node->right);
}

template <typename T>
int BinaryTree<T>::countLeaves() const {
    return countLeavesRecursive(root);
}

template <typename T>
int BinaryTree<T>::countInternalRecursive(Node<T>* node) const {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 0;
    return 1 + countInternalRecursive(node->left) + countInternalRecursive(node->right);
}

template <typename T>
int BinaryTree<T>::countInternal() const {
    return countInternalRecursive(root);
}

template <typename T>
T BinaryTree<T>::findMin() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty!");
    }
    return findMinNode(root)->data;
}

template <typename T>
T BinaryTree<T>::findMax() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty!");
    }
    return findMaxNode(root)->data;
}

template <typename T>
void BinaryTree<T>::printLevelRecursive(Node<T>* node, int level) const {
    if (node == nullptr) return;
    if (level == 0) {
        std::cout << node->data << " ";
    } else {
        printLevelRecursive(node->left, level - 1);
        printLevelRecursive(node->right, level - 1);
    }
}

template <typename T>
void BinaryTree<T>::printLevel(int level) const {
    printLevelRecursive(root, level);
    std::cout << std::endl;
}

#endif// BINARYTREE_TPP
