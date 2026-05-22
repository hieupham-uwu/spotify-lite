#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include "AVL.hpp"

template <typename K, typename V>
struct HashNode {
  K key;
  V value;

  HashNode(const K& k = K{}, const V& v = V{}) : key(k), value(v) {}

  bool operator<(const HashNode& other) const { return key < other.key; }
  bool operator>(const HashNode& other) const { return key > other.key; }
  bool operator==(const HashNode& other) const { return key == other.key; }
};

template <typename K, typename V>

/*
  Usage (Professional Pointer-Return Style):
    1. Initialize a HashTable:
        HashTable<std::string, std::string> myTable(101);

    2. Insert or update a key-value pair:
        myTable.insert("K25", "SongData");

    3. Search and access data safely via find():
        std::string* songPtr = myTable.find("K25");
        if (songPtr != nullptr) {
            std::cout << "Found: " << *songPtr << "\n";
            *songPtr = "UpdatedSongData";
        }

    4. Verify if a key exists:
        if (myTable.contains("K25")) { }

    5. Remove a pair by its key:
        myTable.remove("K25");
*/

class HashTable {
 private:
  std::vector<AVL<HashNode<K, V>>> table;
  size_t totalElements;
  size_t tableSize;

  size_t hashFunction(const K& key) const {
    return std::hash<K>{}(key) % tableSize;
  }

 public:
  explicit HashTable(size_t size = 101) : totalElements(0), tableSize(size) {
    table.resize(tableSize);
}

  ~HashTable() { clear(); }

  void insert(const K& key, const V& value) {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode(key, value);

    HashNode<K, V>* existingNode = table[index].findData(tempNode);

    if (existingNode) {
      existingNode->value = value;
    } else {
      table[index].insert(tempNode);
      ++totalElements;
    }
  }

  bool remove(const K& key) {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode(key, V{});

    if (table[index].search(tempNode)) {
      table[index].remove(tempNode);
      --totalElements;
      return true;
    }
    return false;
  }

  V* find(const K& key) {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode(key, V{});

    HashNode<K, V>* node = table[index].findData(tempNode);
    return node ? &(node->value) : nullptr;
  }

  const V* find(const K& key) const {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode(key, V{});

    const HashNode<K, V>* node = table[index].findData(tempNode);
    return node ? &(node->value) : nullptr;
  }

  bool contains(const K& key) const {
    return find(key) != nullptr;
  }

  size_t size() const { return totalElements; }

  void clear() {
    for (size_t i = 0; i < tableSize; ++i) {
      table[i].clear();
    }
    totalElements = 0;
  }

  bool empty() const { return totalElements == 0; }
};
