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

class STACK {
 private:
  LINKEDLIST<T> list;

 public:
  STACK() = default;
  ~STACK() = default;
  // View elements
  T top() const {
    if (list.empty()) throw std::runtime_error("Stack is empty");
    return list.front();
  }

  // Add elements
  void push(const T& value) { list.push_front(value); }

  // Remove elements
  void pop() {
    if (list.empty()) throw std::runtime_error("Stack is empty");
    list.pop_front();
  }

  // Utility functions
  size_t size() const { return list.size(); }
  bool empty() const { return list.empty(); }

  // Clear the stack
  void clear() { list.clear(); }
};
