#pragma once
#include <stdexcept>

#include "LinkedList.hpp"
using namespace std;
template <typename T>

/*
    All functions:
+ View elements: front(), back()
+ Add elements: enqueue()
+ Remove elements: dequeue()
+ Utility functions: size(), empty()
+ Clear the queue: clear()

*/

class Queue {
 private:
  LinkedList<T> list;

 public:
  Queue() = default;
  ~Queue() = default;
  // View elements
  T front() const {
    if (list.empty()) throw runtime_error("Queue is empty");
    return list.front();
  }

  T back() const {
    if (list.empty()) throw runtime_error("Queue is empty");
    return list.back();
  }

  // Add elements
  void enqueue(const T& value) { list.insertBack(value); }

  // Remove elements
  void dequeue() {
    if (list.empty()) throw runtime_error("Queue is empty");
    list.popFront();
  }

  // Utility functions
  int size() const { return list.size(); }
  bool empty() const { return list.empty(); }

  // Clear the Queue
  void clear() { list.clear(); }
};