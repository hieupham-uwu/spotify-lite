#pragma once

#include <functional>
#include <stdexcept>
#include <vector>
using namespace std;
/*
  Usage:
    1. Sort the ENTIRE vector:
        - Ascending order (Default):
            mergeSort(myVector);
        - Descending order (Using greater):
            mergeSort(myVector, greater<T>());
        - Custom criteria (Using Lambda function for custom structures/objects):
            mergeSort(myVector, [](const MyStruct& a, const MyStruct& b) {
return a.value > b.value; });

    2. Sort a specific range within the vector (e.g., from index 2 to 7):
        - Ascending order within a range:
            mergeSort(myVector, 2, 7);
        - Descending order within a range:
            mergeSort(myVector, 2, 7, greater<T>());

    3. Search for an element in the vector:
        int index = binarySearch(myVector, targetValue);

  All functions:
+ Sorting (Range-based & Full): bubbleSort(), selectionSort(), insertionSort(),
heapSort(), quickSort(), mergeSort()
+ Searching: linearSearch(), binarySearch()

*/

// PART 1: SORTING ALGORITHMS

// --- 1.1. Heap Sort ---
template <typename T, typename Comp>
void heapifyRange(vector<T>& vec, int start, int n, int i, Comp cmp) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && cmp(vec[start + largest], vec[start + l])) largest = l;
  if (r < n && cmp(vec[start + largest], vec[start + r])) largest = r;

  if (largest != i) {
    swap(vec[start + i], vec[start + largest]);
    heapifyRange(vec, start, n, largest, cmp);
  }
}

template <typename T, typename Comp = less<T>>
void heapSort(vector<T>& vec, int left, int right, Comp cmp = Comp{}) {
  if (left >= right || left < 0 || right >= (int)vec.size()) return;

  int n = right - left + 1;
  for (int i = n / 2 - 1; i >= 0; --i) {
    heapifyRange(vec, left, n, i, cmp);
  }
  for (int i = n - 1; i > 0; --i) {
    swap(vec[left], vec[left + i]);
    heapifyRange(vec, left, i, 0, cmp);
  }
}

template <typename T, typename Comp = less<T>>
void heapSort(vector<T>& vec, Comp cmp = Comp{}) {
  if (vec.empty()) return;
  heapSort(vec, 0, (int)vec.size() - 1, cmp);
}

// --- 1.2. Quick Sort ---
template <typename T, typename Comp>
int partition(vector<T>& vec, int lo, int hi, Comp cmp) {
  T pivot = vec[hi];
  int i = lo - 1;
  for (int j = lo; j < hi; ++j) {
    if (cmp(vec[j], pivot)) {
      ++i;
      swap(vec[i], vec[j]);
    }
  }
  swap(vec[i + 1], vec[hi]);
  return i + 1;
}

template <typename T, typename Comp = less<T>>
void quickSort(vector<T>& vec, int lo, int hi, Comp cmp = Comp{}) {
  if (lo < hi && lo >= 0 && hi < (int)vec.size()) {
    int p = partition(vec, lo, hi, cmp);
    quickSort(vec, lo, p - 1, cmp);
    quickSort(vec, p + 1, hi, cmp);
  }
}

template <typename T, typename Comp = less<T>>
void quickSort(vector<T>& vec, Comp cmp = Comp{}) {
  if (vec.empty()) return;
  quickSort(vec, 0, (int)vec.size() - 1, cmp);
}

// --- 1.3. Merge Sort ---
template <typename T, typename Comp>
void merge(vector<T>& vec, int left, int mid, int right, Comp cmp) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<T> L(n1), R(n2);
  for (int i = 0; i < n1; ++i) L[i] = vec[left + i];
  for (int j = 0; j < n2; ++j) R[j] = vec[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (cmp(L[i], R[j]) || (!cmp(R[j], L[i]) && i <= j)) {
      vec[k] = L[i];
      ++i;
    } else {
      vec[k] = R[j];
      ++j;
    }
    ++k;
  }
  while (i < n1) {
    vec[k] = L[i];
    ++i;
    ++k;
  }
  while (j < n2) {
    vec[k] = R[j];
    ++j;
    ++k;
  }
}

template <typename T, typename Comp = less<T>>
void mergeSort(vector<T>& vec, int left, int right, Comp cmp = Comp{}) {
  if (left < right && left >= 0 && right < (int)vec.size()) {
    int mid = left + (right - left) / 2;
    mergeSort(vec, left, mid, cmp);
    mergeSort(vec, mid + 1, right, cmp);
    merge(vec, left, mid, right, cmp);
  }
}

template <typename T, typename Comp = less<T>>
void mergeSort(vector<T>& vec, Comp cmp = Comp{}) {
  if (vec.empty()) return;
  mergeSort(vec, 0, (int)vec.size() - 1, cmp);
}

// --- 1.4. Standard O(N^2) Sorting Functions---
template <typename T, typename Comp = std::less<T>>
void bubbleSort(vector<T>& vec, int left, int right, Comp cmp = Comp{}) {
  if (left >= right || left < 0 || right >= (int)vec.size()) return;

  for (int i = left; i < right; ++i) {
    for (int j = left; j < right - (i - left); ++j) {
      if (cmp(vec[j + 1], vec[j])) {
        swap(vec[j], vec[j + 1]);
      }
    }
  }
}

template <typename T, typename Comp = less<T>>
void bubbleSort(vector<T>& vec, Comp cmp = Comp{}) {
  if (vec.empty()) return;
  bubbleSort(vec, 0, (int)vec.size() - 1, cmp);
}

template <typename T, typename Comp = less<T>>
void selectionSort(vector<T>& vec, int left, int right,
                   Comp cmp = Comp{}) {
  if (left >= right || left < 0 || right >= (int)vec.size()) return;

  for (int i = left; i < right; ++i) {
    int min_idx = i;
    for (int j = i + 1; j <= right; ++j) {
      if (cmp(vec[j], vec[min_idx])) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      swap(vec[i], vec[min_idx]);
    }
  }
}

template <typename T, typename Comp = less<T>>
void selectionSort(vector<T>& vec, Comp cmp = Comp{}) {
  if (vec.empty()) return;
  selectionSort(vec, 0, (int)vec.size() - 1, cmp);
}

template <typename T, typename Comp = less<T>>
void insertionSort(vector<T>& vec, int left, int right,
                   Comp cmp = Comp{}) {
  if (left >= right || left < 0 || right >= (int)vec.size()) return;

  for (int i = left + 1; i <= right; ++i) {
    T key = vec[i];
    int j = i - 1;
    while (j >= left && cmp(key, vec[j])) {
      vec[j + 1] = vec[j];
      --j;
    }
    vec[j + 1] = key;
  }
}

template <typename T, typename Comp = less<T>>
void insertionSort(vector<T>& vec, Comp cmp = Comp{}) {
  if (vec.empty()) return;
  insertionSort(vec, 0, (int)vec.size() - 1, cmp);
}

// PART 2: SEARCHING ALGORITHMS

template <typename T>
int linearSearch(const vector<T>& vec, const T& key) {
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i] == key) return (int)i;
  }
  return -1;
}

template <typename T>
int binarySearch(const vector<T>& vec, const T& key) {
  int lo = 0;
  int hi = (int)vec.size() - 1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (vec[mid] == key) return mid;
    if (vec[mid] < key)
      lo = mid + 1;
    else
      hi = mid - 1;
  }
  return -1;
}
