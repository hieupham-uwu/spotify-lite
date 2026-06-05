#pragma once
#include <stack>
#include <stdexcept>
using namespace std;

template <typename T>

/*
- Support deep copy constructor and assignment operator
  All functions:
+ View elements: front(), back(), find(value) => iterator or nullptr
+ Add elements: insertBack(), insertFront(), insert(it, value), insert(index,
value)
+ Remove elements: popBack(), popFront(), remove(value), removeAt(index),
removeIt(It)
+ Clear the list: clear()
+ Utility functions: size(), empty()
+ Iterators: begin(), end()
+ Special function: reverse()
+ Traversal: traverseForward(void formatShowing()), traverseBackward(void
formatShowing())
*/

class LinkedList {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };
  Node* head;
  Node* tail;
  int sizeLL;

 public:
  class Iterator {
    friend class LinkedList;

   private:
    Node* current;

   public:
    explicit Iterator(Node* node) : current(node) {}

    T& operator*() const {
      if (current == nullptr) throw runtime_error("Iterator out of bounds");
      return current->data;
    }

    Iterator& operator++() {
      if (current == nullptr) throw runtime_error("Iterator out of bounds");
      current = current->next;
      return *this;
    }

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

  LinkedList() : head(nullptr), tail(nullptr), sizeLL(0) {}
  ~LinkedList() { clear(); }

  LinkedList(const LinkedList& other)
      : head(nullptr), tail(nullptr), sizeLL(0) {
    Node* current = other.head;
    while (current != nullptr) {
      insertBack(current->data);
      current = current->next;
    }
  }

  LinkedList& operator=(const LinkedList& other) {
    if (this == &other) return *this;
    clear();

    Node* current = other.head;
    while (current != nullptr) {
      insertBack(current->data);
      current = current->next;
    }
    return *this;
  }

  // View elements
  T front() const {
    if (sizeLL == 0) throw runtime_error("List is empty");
    return head->data;
  }

  T back() const {
    if (sizeLL == 0) throw runtime_error("List is empty");
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

  void traverseForward(void (*showValue)(Node*)) {
    if (sizeLL == 0) return;
    Node* curr = head;
    while (curr != nullptr) {
      showValue(curr);
      curr = curr->next;
    }
  }

  void traverseBackward(void (*showValue)(Node*)) {
    if (sizeLL == 0) return;

    stack<Node*> st;
    Node* curr = head;

    while (curr != nullptr) {
      st.push(curr);
      curr = curr->next;
    }

    while (!st.empty()) {
      Node* top = st.top();
      showValue(top);
      st.pop();
    }
  }

  // Add elements
  void insertBack(const T& value) {
    Node* newNode = new Node(value);
    if (sizeLL == 0) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    ++sizeLL;
  }

  void insertFront(const T& value) {
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
    if (node == nullptr) throw runtime_error("List is empty");
    if (node == head) {
      insertFront(value);
      return;
    }
    Node* current = head;
    while (current != nullptr && current->next != node) {
      current = current->next;
    }
    if (current == nullptr) throw runtime_error("Node not found");
    Node* newNode = new Node(value);
    newNode->next = node;
    current->next = newNode;
    ++sizeLL;
  }

  void insertAt(int index, const T& value) {
    if (index > sizeLL) throw runtime_error("Index out of bounds");
    if (index == 0) {
      insertFront(value);
      return;
    }
    if (index == sizeLL) {
      insertBack(value);
      return;
    }
    Node* newNode = new Node(value);
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    ++sizeLL;
  }

  // Remove elements
  void popBack() {
    if (sizeLL == 0) throw runtime_error("List is empty");
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

  void popFront() {
    if (sizeLL == 0) throw runtime_error("List is empty");
    Node* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
      tail = nullptr;
    }
    --sizeLL;
  }

  void remove(T value) {
    if (sizeLL == 0) return;
    while (head && head->data == value) {
      popFront();
    }

    Node* curr = head;
    Node* prev = nullptr;
    Node* next = nullptr;

    while (curr != nullptr) {
      next = curr->next;
      if (curr->data == value) {
        if (curr == tail) tail = prev;
        prev->next = curr->next;
        delete curr;
        curr = next;
        sizeLL--;
      } else {
        prev = curr;
        curr = next;
      }
    }

    if (head == nullptr) tail = head;
  }

  void removeIt(Iterator it) {
    Node* node = it.current;
    if (node == nullptr) throw runtime_error("List is empty");
    if (node == head) {
      popFront();
      return;
    }
    Node* current = head;
    while (current != nullptr && current->next != node) {
      current = current->next;
    }
    if (current == nullptr) throw runtime_error("Node not found");
    current->next = node->next;
    if (node == tail) {
      tail = current;
    }
    delete node;
    --sizeLL;
  }

  void removeAt(int index) {
    if (index >= sizeLL) throw runtime_error("Index out of bounds");
    if (index == 0) {
      popFront();
      return;
    }
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
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
  int size() const { return sizeLL; }
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
