#ifndef AVL_TREE_TPP
#define AVL_TREE_TPP

// Height convention: an empty subtree has height -1 and a leaf has height 0.
template <typename T>
int AVLTree<T>::nodeHeight(const AVLNode<T>* node) {
    return node == nullptr ? -1 : node->height;
}

template <typename T>
int AVLTree<T>::getBalance(const AVLNode<T>* node) {
    if (node == nullptr) return 0;
    return nodeHeight(node->left) - nodeHeight(node->right);
}

template <typename T>
void AVLTree<T>::updateHeight(AVLNode<T>* node) {
    if (node == nullptr) return;
    int leftHeight = nodeHeight(node->left);
    int rightHeight = nodeHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Right rotation fixes a left-heavy subtree (LL, or part of LR).
template <typename T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* middleSubtree = x->right;

    x->right = y;
    y->left = middleSubtree;

    updateHeight(y); // update the old root first
    updateHeight(x);
    return x;
}

// Left rotation fixes a right-heavy subtree (RR, or part of RL).
template <typename T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* middleSubtree = y->left;

    y->left = x;
    x->right = middleSubtree;

    updateHeight(x); // update the old root first
    updateHeight(y);
    return y;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rebalance(AVLNode<T>* node) {
    if (node == nullptr) return nullptr;

    updateHeight(node);
    int balance = getBalance(node);

    // Left-heavy subtree.
    if (balance > 1) {
        // LR: rotate the left child left, then rotate this node right.
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node); // LL, or completed LR
    }

    // Right-heavy subtree.
    if (balance < -1) {
        // RL: rotate the right child right, then rotate this node left.
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node); // RR, or completed RL
    }

    return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::insertRecursive(AVLNode<T>* node, const T& value, bool& inserted) {
    if (node == nullptr) {
        inserted = true;
        return new AVLNode<T>(value);
    }

    if (value < node->data)
        node->left = insertRecursive(node->left, value, inserted);
    else if (node->data < value)
        node->right = insertRecursive(node->right, value, inserted);
    else
        return node; // Duplicate: do not insert it.

    return rebalance(node);
}

template <typename T>
AVLNode<T>* AVLTree<T>::findMinNode(AVLNode<T>* node) {
    while (node != nullptr && node->left != nullptr) node = node->left;
    return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::findMaxNode(AVLNode<T>* node) {
    while (node != nullptr && node->right != nullptr) node = node->right;
    return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::removeRecursive(AVLNode<T>* node, const T& value, bool& removed) {
    if (node == nullptr) return nullptr;

    if (value < node->data) {
        node->left = removeRecursive(node->left, value, removed);
    } else if (node->data < value) {
        node->right = removeRecursive(node->right, value, removed);
    } else {
        removed = true;

        // Case 1: no children, or only a right child.
        if (node->left == nullptr) {
            AVLNode<T>* replacement = node->right;
            delete node;
            return replacement;
        }

        // Case 2: only a left child.
        if (node->right == nullptr) {
            AVLNode<T>* replacement = node->left;
            delete node;
            return replacement;
        }

        // Case 3: two children. Copy the inorder successor, then remove it.
        AVLNode<T>* successor = findMinNode(node->right);
        node->data = successor->data;
        bool successorRemoved = false;
        node->right = removeRecursive(node->right, successor->data, successorRemoved);
    }

    // Rebalance every ancestor on the path back to the root after deletion.
    return rebalance(node);
}

template <typename T>
AVLNode<T>* AVLTree<T>::searchNode(AVLNode<T>* node, const T& value) {
    while (node != nullptr) {
        if (value < node->data) node = node->left;
        else if (node->data < value) node = node->right;
        else return node;
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::destroyTree(AVLNode<T>* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template <typename T>
int AVLTree<T>::countNodesRecursive(const AVLNode<T>* node) {
    if (node == nullptr) return 0;
    return 1 + countNodesRecursive(node->left) + countNodesRecursive(node->right);
}

template <typename T>
int AVLTree<T>::countLeavesRecursive(const AVLNode<T>* node) {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 1;
    return countLeavesRecursive(node->left) + countLeavesRecursive(node->right);
}

template <typename T>
int AVLTree<T>::countInternalRecursive(const AVLNode<T>* node) {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) return 0;
    return 1 + countInternalRecursive(node->left) + countInternalRecursive(node->right);
}

template <typename T>
void AVLTree<T>::inorderRecursive(const AVLNode<T>* node) {
    if (node == nullptr) return;
    inorderRecursive(node->left);
    std::cout << node->data << ' ';
    inorderRecursive(node->right);
}

template <typename T>
void AVLTree<T>::preorderRecursive(const AVLNode<T>* node) {
    if (node == nullptr) return;
    std::cout << node->data << ' ';
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

template <typename T>
void AVLTree<T>::postorderRecursive(const AVLNode<T>* node) {
    if (node == nullptr) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    std::cout << node->data << ' ';
}

template <typename T>
void AVLTree<T>::printLevelRecursive(const AVLNode<T>* node, int level) {
    if (node == nullptr || level < 0) return;
    if (level == 0) {
        std::cout << node->data << ' ';
        return;
    }
    printLevelRecursive(node->left, level - 1);
    printLevelRecursive(node->right, level - 1);
}

template <typename T>
void AVLTree<T>::printSidewaysRecursive(const AVLNode<T>* node, int depth) {
    if (node == nullptr) return;
    printSidewaysRecursive(node->right, depth + 1);
    for (int i = 0; i < depth; ++i) std::cout << "    ";
    std::cout << node->data << " (h=" << node->height
              << ", BF=" << getBalance(node) << ")\n";
    printSidewaysRecursive(node->left, depth + 1);
}

template <typename T>
void AVLTree<T>::printBalanceFactorsRecursive(const AVLNode<T>* node) {
    if (node == nullptr) return;
    printBalanceFactorsRecursive(node->left);
    std::cout << node->data << ": " << getBalance(node) << '\n';
    printBalanceFactorsRecursive(node->right);
}

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree() { destroyTree(root); }

template <typename T>
bool AVLTree<T>::insert(const T& value) {
    bool inserted = false;
    root = insertRecursive(root, value, inserted);
    return inserted;
}

template <typename T>
bool AVLTree<T>::remove(const T& value) {
    bool removed = false;
    root = removeRecursive(root, value, removed);
    return removed;
}

template <typename T>
bool AVLTree<T>::search(const T& value) const {
    return searchNode(root, value) != nullptr;
}

template <typename T>
bool AVLTree<T>::isEmpty() const { return root == nullptr; }

template <typename T>
int AVLTree<T>::getHeight() const { return nodeHeight(root); }

template <typename T>
int AVLTree<T>::balanceFactor(const T& value) const {
    AVLNode<T>* node = searchNode(root, value);
    if (node == nullptr) throw std::runtime_error("Value not found in AVL tree.");
    return getBalance(node);
}

template <typename T>
int AVLTree<T>::countNodes() const { return countNodesRecursive(root); }

template <typename T>
int AVLTree<T>::countLeaves() const { return countLeavesRecursive(root); }

template <typename T>
int AVLTree<T>::countInternal() const { return countInternalRecursive(root); }

template <typename T>
T AVLTree<T>::findMin() const {
    if (root == nullptr) throw std::runtime_error("Tree is empty!");
    return findMinNode(root)->data;
}

template <typename T>
T AVLTree<T>::findMax() const {
    if (root == nullptr) throw std::runtime_error("Tree is empty!");
    return findMaxNode(root)->data;
}

template <typename T>
void AVLTree<T>::inorder() const { inorderRecursive(root); std::cout << '\n'; }

template <typename T>
void AVLTree<T>::preorder() const { preorderRecursive(root); std::cout << '\n'; }

template <typename T>
void AVLTree<T>::postorder() const { postorderRecursive(root); std::cout << '\n'; }

template <typename T>
void AVLTree<T>::levelOrder() const {
    if (root == nullptr) { std::cout << '\n'; return; }
    LinkedQueue<AVLNode<T>*> queue;
    queue.enqueue(root);
    while (!queue.isEmpty()) {
        AVLNode<T>* current = queue.peek();
        queue.dequeue();
        std::cout << current->data << ' ';
        if (current->left != nullptr) queue.enqueue(current->left);
        if (current->right != nullptr) queue.enqueue(current->right);
    }
    std::cout << '\n';
}

template <typename T>
void AVLTree<T>::printLevel(int level) const {
    if (level < 0) { std::cout << '\n'; return; }
    printLevelRecursive(root, level);
    std::cout << '\n';
}

template <typename T>
void AVLTree<T>::printSideways() const {
    if (root == nullptr) { std::cout << "(empty tree)\n"; return; }
    printSidewaysRecursive(root, 0);
}

template <typename T>
void AVLTree<T>::printBalanceFactors() const {
    if (root == nullptr) { std::cout << "(empty tree)\n"; return; }
    printBalanceFactorsRecursive(root);
}

template <typename T>
void AVLTree<T>::clear() {
    destroyTree(root);
    root = nullptr;
}

#endif // AVL_TREE_TPP
