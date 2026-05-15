#pragma once
#include <stdexcept>

#include "LinkedList.hpp"
template <typename T>

/*
    All functions:
+ View elements: front(), back()
+ Add elements: push()
+ Remove elements: pop()
+ Utility functions: getSize(), empty()

*/

class QUEUE {
 private:
  LINKEDLIST<T> list;

 public:
  QUEUE() = default;
  ~QUEUE() = default;
  // View elements
  T front() const {
    if (list.empty()) throw std::runtime_error("Queue is empty");
    return list.front();
  }

  T back() const {
    if (list.empty()) throw std::runtime_error("Queue is empty");
    return list.back();
  }

  // Add elements
  void push(const T& value) { list.push_back(value); }

  // Remove elements
  void pop() {
    if (list.empty()) throw std::runtime_error("Queue is empty");
    list.pop_front();
  }

  // Utility functions
  size_t getSize() const { return list.getSize(); }

  bool empty() const { return list.empty(); }
};