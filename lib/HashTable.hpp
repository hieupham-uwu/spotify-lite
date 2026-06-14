#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include "AVL.hpp"
using namespace std;
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
        HashTable<string, string> myTable(101);

    2. Insert or update a key-value pair:
        myTable.insert("K25", "SongData");

    3. Search and access data safely via find():
        string* songPtr = myTable.find("K25");
        if (songPtr != nullptr) {
            cout << "Found: " << *songPtr << "\n";
            *songPtr = "UpdatedSongData";
        }

    4. Verify if a key exists:
        if (myTable.contains("K25")) { }

    5. Remove a pair by its key:
        myTable.remove("K25");
*/

class HashTable {
 private:
  vector<AVL<HashNode<K, V>>> table;
  int totalElements;
  int tableSize;

  template <typename T>
int genericHash(const T& key) const {
    const unsigned char* p = (const unsigned char*)&key;
    int hashValue = 0;

    for (int i = 0; i < sizeof(T); i++) {
        hashValue = (hashValue * 31 + p[i]) % tableSize;
    }

    return hashValue;
}

int genericHash(const string& key) const {
    int hashValue = 0;

    for (int i = 0; i < key.length(); i++) {
        hashValue = (hashValue * 31 + key[i]) % tableSize;
    }

    return hashValue;
}

int hashFunction(const K& key) const {
    return genericHash(key);
}

 public:
  explicit HashTable(int size = 101) : totalElements(0), tableSize(size) {
    table.resize(tableSize);
}

  ~HashTable() { clear(); }

  void insert(const K& key, const V& value) {
    int index = hashFunction(key);
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
    int index = hashFunction(key);
    HashNode<K, V> tempNode(key, V{});

    if (table[index].search(tempNode)) {
      table[index].remove(tempNode);
      --totalElements;
      return true;
    }
    return false;
  }

  V* find(const K& key) {
    int index = hashFunction(key);
    HashNode<K, V> tempNode(key, V{});

    HashNode<K, V>* node = table[index].findData(tempNode);
    return node ? &(node->value) : nullptr;
  }

  const V* find(const K& key) const {
    int index = hashFunction(key);
    HashNode<K, V> tempNode(key, V{});

    const HashNode<K, V>* node = table[index].findData(tempNode);
    return node ? &(node->value) : nullptr;
  }

  bool contains(const K& key) const {
    return find(key) != nullptr;
  }

  int size() const { return totalElements; }

  void clear() {
    for (int i = 0; i < tableSize; ++i) {
      table[i].clear();
    }
    totalElements = 0;
  }

  bool empty() const { return totalElements == 0; }
};
