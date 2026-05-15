#pragma once

#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename Comp = std::less<T>>

/*
 Uasge:
    1. Default is a max-heap:
        PRIORITYQUEUE<int> pq;
    2. For a min-heap:
        PRIORITYQUEUE<int, std::greater<int>> pq;

    All functions:
+ View elements: top()
+ Add elements: push()
+ Remove elements: pop()
+ Utility functions: empty(), size()
+ Clear the queue: clear()

*/

struct PRIORITYQUEUE {
 private:
  std::vector<T> data;
  Comp cmp;

  int parent(int i) const { return (i - 1) / 2; }
  int left(int i) const { return 2 * i + 1; }
  int right(int i) const { return 2 * i + 2; }

  void heapifyUp(int i) {
    while (i > 0 && cmp(data[parent(i)], data[i])) {
      std::swap(data[parent(i)], data[i]);
      i = parent(i);
    }
  }

  void heapifyDown(int i) {
    int best = i;
    int l = left(i);
    int r = right(i);
    int n = (int)data.size();

    if (l < n && cmp(data[best], data[l])) best = l;
    if (r < n && cmp(data[best], data[r])) best = r;

    if (best != i) {
      std::swap(data[i], data[best]);
      heapifyDown(best);
    }
  }

 public:
  explicit PRIORITYQUEUE(Comp c = Comp{}) : cmp(c) {}

  explicit PRIORITYQUEUE(const std::vector<T>& vec, Comp c = Comp{})
      : data(vec), cmp(c) {
    int n = (int)data.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapifyDown(i);
  }

  // Add elements
  void push(const T& item) {
    data.push_back(item);
    heapifyUp((int)data.size() - 1);
  }

  // Remove elements
  void pop() {
    if (empty()) throw std::runtime_error("PRIORITYQUEUE is empty");

    std::swap(data[0], data.back());
    data.pop_back();

    if (!empty()) heapifyDown(0);
  }

  // View elements
  const T& top() const {
    if (empty()) throw std::runtime_error("PRIORITYQUEUE is empty");
    return data[0];
  }

  // Utility functions
  bool empty() const { return data.empty(); }
  size_t size() const { return data.size(); }

  // Clear the queue
  void clear() { data.clear(); }
};