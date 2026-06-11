#pragma once

#include <string>

#include "../../lib/LinkedList.hpp"

using namespace std;

struct Playlist {
  string name;
  LinkedList<string> songIds;

  Playlist() { name = ""; }

  Playlist(string name) { this->name = name; }

  bool addSongId(const string& songId) {
    if (songId.empty()) return false;

    if (containsSongId(songId)) return false;

    songIds.insertBack(songId);
    return true;
  }

  bool removeSongId(const string& songId) {
    auto it = songIds.find(songId);

    if (it == songIds.end()) return false;

    songIds.removeIt(it);
    return true;
  }

  bool containsSongId(const string& songId) const {
    auto it = songIds.find(songId);
    return it != songIds.end();
  }

  void clear() { songIds.clear(); }

  int size() const { return songIds.size(); }

  bool empty() const { return songIds.empty(); }
};
