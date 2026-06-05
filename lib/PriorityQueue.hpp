#pragma once

#include <functional>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T, typename Comp = less<T>>

/*
 Usage:
    1. Default is a max-heap:
        PriorityQueue<int> pq;
    2. For a min-heap:
        PriorityQueue<int, greater<int>> pq;

    All functions:
+ View elements: peek()
+ Add elements: insert()
+ Remove elements: extract()
+ Utility functions: empty(), size()
+ Clear the queue: clear()

*/

class PriorityQueue {
 private:
  vector<T> data;
  Comp cmp;

  int parent(int i) const { return (i - 1) / 2; }
  int left(int i) const { return 2 * i + 1; }
  int right(int i) const { return 2 * i + 2; }

  void heapifyUp(int i) {
    while (i > 0 && cmp(data[parent(i)], data[i])) {
      swap(data[parent(i)], data[i]);
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
      swap(data[i], data[best]);
      heapifyDown(best);
    }
  }

 public:
  explicit PriorityQueue(Comp c = Comp{}) : cmp(c) {}

  explicit PriorityQueue(const vector<T>& vec, Comp c = Comp{})
      : data(vec), cmp(c) {
    int n = (int)data.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapifyDown(i);
  }

  // Add elements
  void insert(const T& item) {
    data.push_back(item);
    heapifyUp((int)data.size() - 1);
  }

  // Remove elements
  T extract() {
    if (empty()) throw runtime_error("PriorityQueue is empty");
    T top = peek();
    swap(data[0], data.back());
    data.pop_back();

    if (!empty()) heapifyDown(0);

    return top;
  }

  // View elements
  const T& peek() const {
    if (empty()) throw runtime_error("PriorityQueue is empty");
    return data[0];
  }

  // Utility functions
  bool empty() const { return data.empty(); }
  int size() const { return data.size(); }

  // Clear the queue
  void clear() { data.clear(); }
};