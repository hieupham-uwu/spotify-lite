#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include "AVL.hpp" 

template <typename K, typename V>
struct HashNode {
  K key;
  V value;

  // Overloading operators so the AVL tree routes and compares based strictly on KEY
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
            std::cout << "Found: " << *songPtr << "\n"; // Access value via *
            *songPtr = "UpdatedSongData";             // Modify value directly in memory!
        } else {
            std::cout << "Not found!\n";
        }

    4. Verify if a key exists:
        if (myTable.contains("K25")) { // Key exists }

    5. Remove a pair by its key:
        myTable.remove("K25");
*/

class HashTable {
 private:
  // Each bucket inside the vector is an independent self-balancing AVL tree
  std::vector<AVL<HashNode<K, V>>> table;
  size_t totalElements;
  size_t tableSize;

  // Standard index compression using C++ built-in std::hash
  size_t hashFunction(const K& key) const {
    return std::hash<K>{}(key) % tableSize;
  }

 public:
  // ============================================================================
  // PUBLIC API FUNCTIONS
  // ============================================================================

  explicit HashTable(size_t size = 101) : tableSize(size), totalElements(0) {
    table.resize(tableSize);
  }

  ~HashTable() { clear(); }

  // IN-PLACE INSERT: If key exists, update value directly. Otherwise, insert new.
  void insert(const K& key, const V& value) {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode{key, value};

    // Ask the AVL tree at this bucket to find if the key already exists
    HashNode<K, V>* existingNode = table[index].findData(tempNode);

    if (existingNode != nullptr) {
      existingNode->value = value; // Overwrite value directly in memory without rotation
    } else {
      table[index].insert(tempNode); // Insert fresh node into AVL
      ++totalElements;
    }
  }

  // Removes a pair from the table. Returns true if found and removed.
  bool remove(const K& key) {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode{key, V{}};

    if (table[index].search(tempNode)) {
      table[index].remove(tempNode);
      --totalElements;
      return true;
    }
    return false;
  }

  // Finds and returns a POINTER to the value inside the table. Returns nullptr if not found.
  V* find(const K& key) {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode{key, V{}};
    
    HashNode<K, V>* targetNode = table[index].findData(tempNode);
    if (targetNode != nullptr) {
      return &(targetNode->value); // Returns direct memory address of the value
    }
    return nullptr;
  }

  // Const overload of find() for read-only access
  const V* find(const K& key) const {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode{key, V{}};
    
    // Cast away const safely to query the read-only loop from the AVL bucket
    HashNode<K, V>* targetNode = const_cast<AVL<HashNode<K, V>>&>(table[index]).findData(tempNode);
    if (targetNode != nullptr) {
      return &(targetNode->value);
    }
    return nullptr;
  }

  // Verifies the existence of a key inside the table
  bool contains(const K& key) const {
    size_t index = hashFunction(key);
    HashNode<K, V> tempNode{key, V{}};
    return table[index].search(tempNode);
  }

  // Returns the total number of key-value pairs
  size_t size() const { 
    return totalElements; 
  }

  // Wipes out all elements from all AVL buckets
  void clear() {
    for (size_t i = 0; i < tableSize; ++i) {
      table[i].clear();
    }
    totalElements = 0;
  }

  // Check if the table is empty
  bool empty() const { 
    return totalElements == 0; 
  }
};
