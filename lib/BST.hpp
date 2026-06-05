#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;
template <typename T>
struct BSTNode {
  T data;
  BSTNode* left;
  BSTNode* right;

  BSTNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>

/*
  Usage:
    1. Initialize an empty tree:
        BST<int> myTree;

    2. Insert elements into the tree:
        myTree.insert(50);
        myTree.insert(30);

    3. Search for a value:
        if (myTree.search(30)) { // Found }

    4. Traverse the tree (Prints directly to Console):
        myTree.traverseInOrder(); // Prints in ascending order

    5. Remove an element:
        myTree.remove(30);

    6. Clear the entire tree:
        myTree.clear();

  All functions:
+ Add elements: insert()
+ Remove elements: remove()
+ Search elements: search()
+ Traversals: traversePreOrder(), traverseInOrder(), traversePostOrder()
+ Utility functions: clear(), empty()

*/

struct BST {
 private:
  BSTNode<T>* root;

  // PRIVATE HELPER FUNCTIONS (INTERNAL RECURSIVE LOGIC)

  void insertHelper(BSTNode<T>*& node, const T& val) {
    if (node == nullptr) {
      node = new BSTNode<T>(val);
      return;
    }
    if (val < node->data) {
      insertHelper(node->left, val);
    } else if (val > node->data) {
      insertHelper(node->right, val);
    }
  }

  bool searchHelper(BSTNode<T>* node, const T& val) const {
    if (node == nullptr) return false;
    if (node->data == val) return true;
    if (val < node->data) return searchHelper(node->left, val);
    return searchHelper(node->right, val);
  }

  BSTNode<T>* findMin(BSTNode<T>* node) const {
    while (node != nullptr && node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  void removeHelper(BSTNode<T>*& node, const T& val) {
    if (node == nullptr) return; 

    if (val < node->data) {
      removeHelper(node->left, val);
    } else if (val > node->data) {
      removeHelper(node->right, val);
    } else {
      
      if (node->left == nullptr) {
        BSTNode<T>* temp = node->right;
        delete node;
        node = temp;
      } 
      else if (node->right == nullptr) {
        BSTNode<T>* temp = node->left;
        delete node;
        node = temp;
      } 
      else {
        BSTNode<T>* temp = findMin(node->right);
        
        node->data = temp->data;
        
        removeHelper(node->right, temp->data);
      }
    }
  }

  void clearHelper(BSTNode<T>*& node) {
    if (node == nullptr) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
    node = nullptr;
  }

  void preOrderHelper(BSTNode<T>* node) const {
    if (node == nullptr) return;
    cout << node->data << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }

  void inOrderHelper(BSTNode<T>* node) const {
    if (node == nullptr) return;
    inOrderHelper(node->left);
    cout << node->data << " ";
    inOrderHelper(node->right);
  }

  void postOrderHelper(BSTNode<T>* node) const {
    if (node == nullptr) return;
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    cout << node->data << " ";
  }

 public:
  // PUBLIC API FUNCTIONS

  BST() : root(nullptr) {}

  ~BST() { clear(); }

  void insert(const T& val) { insertHelper(root, val); }

  void remove(const T& val) { removeHelper(root, val); }

  bool search(const T& val) const { return searchHelper(root, val); }

  void clear() { clearHelper(root); }

  bool empty() const { return root == nullptr; }

  void traversePreOrder() const {
    preOrderHelper(root);
    cout << "\n";
  }

  void traverseInOrder() const {
    inOrderHelper(root);
    cout << "\n";
  }

  void traversePostOrder() const {
    postOrderHelper(root);
    cout << "\n";
  }
};
