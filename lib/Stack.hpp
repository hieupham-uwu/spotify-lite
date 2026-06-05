#pragma once
#include <stdexcept>

#include "LinkedList.hpp"
template <typename T>

/*
    All functions:
+ View elements: top()
+ Add elements: push()
+ Remove elements: pop()
+ Utility functions: size(), empty()
+ Clear the stack: clear()

*/

class Stack {
 private:
  LinkedList<T> list;

 public:
  Stack() = default;
  ~Stack() = default;
  // View elements
  T top() const {
    if (list.empty()) throw runtime_error("Stack is empty");
    return list.front();
  }

  // Add elements
  void push(const T& value) { list.insertFront(value); }

  // Remove elements
  void pop() {
    if (list.empty()) throw runtime_error("Stack is empty");
    list.popFront();
  }

  // Utility functions
  int size() const { return list.size(); }
  bool empty() const { return list.empty(); }

  // Clear the Stack
  void clear() { list.clear(); }
};
