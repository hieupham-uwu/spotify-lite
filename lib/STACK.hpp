#pragma once
#include <stdexcept>

#include "LinkedList.hpp"
template <typename T>

/*
    All functions:
+ View elements: top()
+ Add elements: push()
+ Remove elements: pop()
+ Utility functions: getSize(), empty()

*/

class STACK {
 private:
  LINKEDLIST<T> list;

 public:
  STACK() = default;
  ~STACK() = default;
  // View elements
  T top() const {
    if (list.empty()) throw std::runtime_error("Stack is empty");
    return list.back();
  }

  // Add elements
  void push(const T& value) { list.push_back(value); }

  // Remove elements
  void pop() {
    if (list.empty()) throw std::runtime_error("Stack is empty");
    list.pop_back();
  }

  // Utility functions
  size_t getSize() const { return list.getSize(); }

  bool empty() const { return list.empty(); }
};
