#pragma once
#include <stdexcept>
template <typename T>

/*
- Support deep copy constructor and assignment operator
  All functions:
+ View elements: front(), back(), find(value) => iterator or nullptr
+ Add elements: push_back(), push_front(), insert(it, value), insert(index,
value)
+ Remove elements: pop_back(), pop_front(), erase(it), erase(index)
+ Clear the list: clear()
+ Utility functions: size(), empty()
+ Iterators: begin(), end()
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
  size_t sizeLL;

 public:
  class Iterator {
    friend class LINKEDLIST;

   private:
    Node* current;

   public:
    explicit Iterator(Node* node) : current(node) {}

    T& operator*() const {
      if (current == nullptr)
        throw std::runtime_error("Iterator out of bounds");
      return current->data;
    }
    // Pre-increment ++iterator
    Iterator& operator++() {
      if (current == nullptr)
        throw std::runtime_error("Iterator out of bounds");
      current = current->next;
      return *this;
    }
    // Post-increment iterator++
    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator!=(const Iterator& other) const {
      return current != other.current;
    }

    bool operator==(const Iterator& other) const {
      return current == other.current;
    }
  };

  LINKEDLIST() : head(nullptr), tail(nullptr), sizeLL(0) {}
  ~LINKEDLIST() { clear(); }

  // Deep copy constructor
  LINKEDLIST(const LINKEDLIST& other)
      : head(nullptr), tail(nullptr), sizeLL(0) {
    Node* current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }

  LINKEDLIST& operator=(const LINKEDLIST& other) {
    if (this == &other) return *this;
    clear();

    Node* current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
    return *this;
  }

  // View elements
  T front() const {
    if (sizeLL == 0) throw std::runtime_error("List is empty");
    return head->data;
  }

  T back() const {
    if (sizeLL == 0) throw std::runtime_error("List is empty");
    return tail->data;
  }

  Iterator find(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
      if (current->data == value) {
        return Iterator(current);
      }
      current = current->next;
    }
    return end();  // Not found
  }

  // Add elements
  void push_back(const T& value) {
    Node* newNode = new Node(value);
    if (sizeLL == 0) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    ++sizeLL;
  }

  void push_front(const T& value) {
    Node* newNode = new Node(value);
    if (sizeLL == 0) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
    ++sizeLL;
  }

  void insert(Iterator it, const T& value) {
    Node* node = it.current;
    if (node == nullptr) throw std::runtime_error("Node is null");
    if (node == head) {
      push_front(value);
      return;
    }
    Node* current = head;
    while (current != nullptr && current->next != node) {
      current = current->next;
    }
    if (current == nullptr) throw std::runtime_error("Node not found");
    Node* newNode = new Node(value);
    newNode->next = node;
    current->next = newNode;
    ++sizeLL;
  }

  void insert(size_t index, const T& value) {
    if (index > sizeLL) throw std::runtime_error("Index out of bounds");
    if (index == 0) {
      push_front(value);
      return;
    }
    if (index == sizeLL) {
      push_back(value);
      return;
    }
    Node* newNode = new Node(value);
    Node* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    ++sizeLL;
  }

  // Remove elements
  void pop_back() {
    if (sizeLL == 0) throw std::runtime_error("List is empty");
    if (sizeLL == 1) {
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
    --sizeLL;
  }

  void pop_front() {
    if (sizeLL == 0) throw std::runtime_error("List is empty");
    Node* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
      tail = nullptr;
    }
    --sizeLL;
  }

  void erase(Iterator it) {
    Node* node = it.current;
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
    --sizeLL;
  }

  void erase(size_t index) {
    if (index >= sizeLL) throw std::runtime_error("Index out of bounds");
    if (index == 0) {
      pop_front();
      return;
    }
    Node* current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    Node* temp = current->next;
    current->next = temp->next;
    if (temp == tail) {
      tail = current;
    }
    delete temp;
    --sizeLL;
  }

  // Clear the list
  void clear() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    head = tail = nullptr;
    sizeLL = 0;
  }

  // Utility functions
  size_t size() const { return sizeLL; }
  bool empty() const { return sizeLL == 0; }

  // Iterator
  Iterator begin() const { return Iterator(head); }
  Iterator end() const { return Iterator(nullptr); }

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
