#pragma once
#include <stdexcept>
template <typename T>

/*
  All functions:
+ View elements: front(), back()
+ Add elements: push_back(), push_front(), insert()
+ Remove elements: pop_back(), pop_front(), erase()
+ Clear the list: clear()
+ Utility functions: getSize(), empty()
+ Iterators: begin(), end(), rbegin(), rend()
+ Special function: reverse()

*/

class LINKEDLIST {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };
  Node* head;
  Node* tail;
  size_t size;

 public:
  LINKEDLIST() : head(nullptr), tail(nullptr), size(0) {}
  ~LINKEDLIST() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    head = tail = nullptr;
    size = 0;
  }

  // View elements
  T front() const {
    if (size == 0) throw std::runtime_error("List is empty");
    return head->data;
  }

  T back() const {
    if (size == 0) throw std::runtime_error("List is empty");
    return tail->data;
  }

  // Add elements
  void push_back(const T& value) {
    Node* newNode = new Node(value);
    if (size == 0) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    ++size;
  }

  void push_front(const T& value) {
    Node* newNode = new Node(value);
    if (size == 0) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
    ++size;
  }

  void insert(LINKEDLIST<T>::Node* node, const T& value) {
    if (node == nullptr) throw std::runtime_error("Node is null");
    Node* newNode = new Node(value);
    if (node == head) {
      push_front(value);
      return;
    }
    Node* current = head;
    while (current != nullptr && current->next != node) {
      current = current->next;
    }
    if (current == nullptr) throw std::runtime_error("Node not found");
    newNode->next = node;
    current->next = newNode;
    ++size;
  }

  // Remove elements
  void pop_back() {
    if (size == 0) throw std::runtime_error("List is empty");
    if (size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      Node* current = head;
      while (current->next != tail) {
        current = current->next;
      }
      delete tail;
      tail = current;
      tail->next = nullptr;
    }
    --size;
  }

  void pop_front() {
    if (size == 0) throw std::runtime_error("List is empty");
    Node* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
      tail = nullptr;
    }
    --size;
  }

  void erase(LINKEDLIST<T>::Node* node) {
    if (node == nullptr) throw std::runtime_error("Node is null");
    if (node == head) {
      pop_front();
      return;
    }
    Node* current = head;
    while (current != nullptr && current->next != node) {
      current = current->next;
    }
    if (current == nullptr) throw std::runtime_error("Node not found");
    current->next = node->next;
    if (node == tail) {
      tail = current;
    }
    delete node;
    --size;
  }

  // Clear the list
  void clear() { ~*this; }

  // Utility functions
  size_t getSize() const { return size; }
  bool empty() const { return size == 0; }

  // Iterator
  Node* begin() const { return head; }
  Node* end() const { return nullptr; }
  Node* rbegin() const { return tail; }
  Node* rend() const { return nullptr; }

  // Special function
  void reverse() {
    Node* prev = nullptr;
    Node* current = head;
    tail = head;  // Update tail to the original head
    while (current != nullptr) {
      Node* nextNode = current->next;
      current->next = prev;
      prev = current;
      current = nextNode;
    }
    head = prev;  // Update head to the new front
  }
};
