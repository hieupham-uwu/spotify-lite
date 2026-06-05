#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
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

    6. Traversal:
        vector<int> values = myAVL.inorder();
        vector<int> values = myAVL.preorder();
        vector<int> values = myAVL.postorder();

    7. Convert to vector:
        vector<int> values = myAVL.toVector();

  All functions:
+ Add elements: insert()
+ Remove elements: remove()
+ Search elements: search()
+ Utility functions: clear(), empty()
+ Traversal: inorder(), preorder(), postorder()
+ Convert: toVector()
*/

class AVL {
 private:
  AVLNode<T>* root;

  int getHeight(AVLNode<T>* node) const { return node ? node->height : 0; }

  int getBalance(AVLNode<T>* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
  }

  void update(AVLNode<T>* node) {
    if (node) {
      node->height =
          max(getHeight(node->left), getHeight(node->right)) + 1;
    }
  }

  void rightRotate(AVLNode<T>*& node) {
    AVLNode<T>* L = node->left;
    AVLNode<T>* rL = L->right;

    L->right = node;
    node->left = rL;

    update(node);
    update(L);

    node = L;
  }

  void leftRotate(AVLNode<T>*& node) {
    AVLNode<T>* R = node->right;
    AVLNode<T>* lR = R->left;

    R->left = node;
    node->right = lR;

    update(node);
    update(R);

    node = R;
  }

  void rebalance(AVLNode<T>*& node) {
    if (!node) return;

    update(node);
    int balance = getBalance(node);

    if (balance > 1) {
      if (getBalance(node->left) < 0) {
        leftRotate(node->left);
      }
      rightRotate(node);
    } else if (balance < -1) {
      if (getBalance(node->right) > 0) {
        rightRotate(node->right);
      }
      leftRotate(node);
    }
  }

  void insertHelper(AVLNode<T>*& node, const T& val) {
    if (!node) {
      node = new AVLNode<T>(val);
      return;
    }

    if (val < node->data)
      insertHelper(node->left, val);
    else if (val > node->data)
      insertHelper(node->right, val);
    else
      return;

    rebalance(node);
  }

  void removeHelper(AVLNode<T>*& node, const T& val) {
    if (!node) return;

    if (val < node->data)
      removeHelper(node->left, val);
    else if (val > node->data)
      removeHelper(node->right, val);
    else {
      if (!node->left || !node->right) {
        AVLNode<T>* temp = node->left ? node->left : node->right;
        delete node;
        node = temp;
      } else {
        AVLNode<T>* temp = node->right;
        while (temp->left) temp = temp->left;
        node->data = temp->data;
        removeHelper(node->right, temp->data);
      }
    }

    if (node) rebalance(node);
  }

  bool searchHelper(AVLNode<T>* node, const T& val) const {
    if (!node) return false;
    if (node->data == val) return true;
    if (val < node->data) return searchHelper(node->left, val);
    return searchHelper(node->right, val);
  }

  void clearHelper(AVLNode<T>*& node) {
    if (!node) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
    node = nullptr;
  }

  // ==========================
  // TRAVERSAL HELPERS
  // ==========================

  void inorderHelper(AVLNode<T>* node, std::vector<T>& result) const {
    if (!node) return;

    inorderHelper(node->left, result);
    result.push_back(node->data);
    inorderHelper(node->right, result);
  }

  void preorderHelper(AVLNode<T>* node, std::vector<T>& result) const {
    if (!node) return;

    result.push_back(node->data);
    preorderHelper(node->left, result);
    preorderHelper(node->right, result);
  }

  void postorderHelper(AVLNode<T>* node, std::vector<T>& result) const {
    if (!node) return;

    postorderHelper(node->left, result);
    postorderHelper(node->right, result);
    result.push_back(node->data);
  }

 public:
  AVL() : root(nullptr) {}
  ~AVL() { clear(); }

  void insert(const T& val) { insertHelper(root, val); }
  void remove(const T& val) { removeHelper(root, val); }
  bool search(const T& val) const { return searchHelper(root, val); }
  void clear() { clearHelper(root); }
  bool empty() const { return root == nullptr; }

  // ==========================
  // TRAVERSAL FUNCTIONS
  // ==========================

  vector<T> inorder() const {
    vector<T> result;
    inorderHelper(root, result);
    return result;
  }

  vector<T> preorder() const {
    vector<T> result;
    preorderHelper(root, result);
    return result;
  }

  vector<T> postorder() const {
    vector<T> result;
    postorderHelper(root, result);
    return result;
  }

  vector<T> toVector() const {
    return inorder();
  }

  // ==========================
  // EXTENSION FOR HASHTABLE
  // ==========================

  // Non-const version (can modify data)
  T* findData(const T& val) {
    AVLNode<T>* current = root;
    while (current) {
      if (val == current->data) return &(current->data);
      if (val < current->data)
        current = current->left;
      else
        current = current->right;
    }
    return nullptr;
  }

  // Const version (read-only)
  const T* findData(const T& val) const {
    AVLNode<T>* current = root;
    while (current) {
      if (val == current->data) return &(current->data);
      if (val < current->data)
        current = current->left;
      else
        current = current->right;
    }
    return nullptr;
  }
};
