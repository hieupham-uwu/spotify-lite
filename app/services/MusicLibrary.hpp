#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include<vector>

#include "../../lib/AVL.hpp"
#include "../../lib/HASHTABLE.hpp"
#include "../models/Song.hpp"
#include "../utilities/StringUtils.hpp"

using namespace std;

class MusicLibrary {
 private:
  HashTable<string, Song> songsByID;
  HashTable<string, Song> songsByName;
  AVL<Song> allSongs;
  size_t songCount = 0;

  void syncSongIndexes(const Song& song);  // Update Song Table
  void updateSongInAllSongs(
      const Song& song);  // Update a song in list allSongs

 public:
  MusicLibrary();
  bool loadFromFile(const string& fileName);

  void addSong(const Song& song);

  Song* findById(string id);
  Song* findByTitle(string title);

  bool increasePlayCount(string id);
  bool increaseLikeCount(string id);

  const AVL<Song>& getAllSongs() const;
  vector<Song> getAllSongsVector() const;
  size_t size() const;
  
  
};
