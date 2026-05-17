#pragma once

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
struct AVLNode {
  T data;
  int height;
  AVLNode* left;
  AVLNode* right;

  AVLNode(const T& val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>

/*
  Usage:
    1. Initialize an empty AVL-based balanced tree:
        AVL<int> myAVL;

    2. Insert elements (The tree automatically auto-balances via rotations):
        myAVL.insert(10);
        myAVL.insert(20);

    3. Search for an element:
        if (myAVL.search(20)) { // Found and guaranteed O(log N) efficiency }

    4. Remove an element (Tree re-balances automatically after deletion):
        myAVL.remove(10);

    5. Utility functions:
        myAVL.clear();
        if (myAVL.empty()) { // Tree contains no nodes }

  All functions:
+ Add elements: insert()
+ Remove elements: remove()
+ Search elements: search()
+ Utility functions: clear(), empty()

*/

struct AVL {
 private:
  AVLNode<T>* root;

  // PART 1: PRIVATE HELPER FUNCTIONS

  int getHeight(AVLNode<T>* node) const {
    return node ? node->height : 0;
  }

  int getBalance(AVLNode<T>* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
  }

  void update(AVLNode<T>* node) {
    if (node != nullptr) {
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
  }

  // Rotates right to fix Left-Left (LL) imbalance
  void rightRotate(AVLNode<T>*& node) {
    AVLNode<T>* L = node->left;
    AVLNode<T>* rL = L->right;

    L->right = node;
    node->left = rL;

    update(node);
    update(L);

    node = L; 
  }

  // Rotates left to fix Right-Right (RR) imbalance
  void leftRotate(AVLNode<T>*& node) {
    AVLNode<T>* R = node->right;
    AVLNode<T>* lR = R->left;

    R->left = node;
    node->right = lR;

    update(node);
    update(R);

    node = R; 
  }

  // Evaluates balance factor and triggers required rotations
  void rebalance(AVLNode<T>*& node) {
    if (node == nullptr) return;

    update(node);
    int balance = getBalance(node);

    // Left-heavy cases
    if (balance > 1) {
      if (getBalance(node->left) < 0) {
        leftRotate(node->left); // Left-Right (LR) Case
      }
      rightRotate(node); // Left-Left (LL) Case
    }
    // Right-heavy cases
    else if (balance < -1) {
      if (getBalance(node->right) > 0) {
        rightRotate(node->right); // Right-Left (RL) Case
      }
      leftRotate(node); // Right-Right (RR) Case
    }
  }

  void insertHelper(AVLNode<T>*& node, const T& val) {
    if (node == nullptr) {
      node = new AVLNode<T>(val);
      return;
    }

    if (val < node->data) {
      insertHelper(node->left, val);
    } else if (val > node->data) {
      insertHelper(node->right, val);
    } else {
      return; // Duplicates are not allowed
    }

    rebalance(node);
  }

  AVLNode<T>* findMin(AVLNode<T>* node) const {
    while (node != nullptr && node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  void removeHelper(AVLNode<T>*& node, const T& val) {
    if (node == nullptr) return;

    if (val < node->data) {
      removeHelper(node->left, val);
    } else if (val > node->data) {
      removeHelper(node->right, val);
    } else {
      // Node to delete found
      if (node->left == nullptr || node->right == nullptr) {
        AVLNode<T>* temp = node->left ? node->left : node->right;
        delete node;
        node = temp;
      } else {
        // Node with two children
        AVLNode<T>* temp = findMin(node->right);
        node->data = temp->data;
        removeHelper(node->right, temp->data);
      }
    }

    if (node == nullptr) return;

    rebalance(node);
  }

  bool searchHelper(AVLNode<T>* node, const T& val) const {
    if (node == nullptr) return false;
    if (node->data == val) return true;
    if (val < node->data) return searchHelper(node->left, val);
    return searchHelper(node->right, val);
  }

  void clearHelper(AVLNode<T>*& node) {
    if (node == nullptr) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
    node = nullptr;
  }

 public:
 	
  // PART 2: PUBLIC API FUNCTIONS

  AVL() : root(nullptr) {}

  ~AVL() { clear(); }

  void insert(const T& val) { insertHelper(root, val); }

  void remove(const T& val) { removeHelper(root, val); }

  bool search(const T& val) const { return searchHelper(root, val); }

  void clear() { clearHelper(root); }

  bool empty() const { return root == nullptr; }
};
