#pragma once

#include <fstream>
#include <string>
using namespace std;

struct Song {
  string id;
  string title;
  string artist;
  string genre;
  int duration;  // seconds
  int playCount;
  int likeCount;
  Song() {
    this->id = "";
    this->title = "";
    this->artist = "";
    this->genre = "";
    this->duration = 0;
    this->likeCount = 0;
    this->playCount = 0;
  }
  Song(string id, string title, string artist, string genre, int duration,
       int playCount = 0, int likeCount = 0) {
    this->id = id;
    this->title = title;
    this->artist = artist;
    this->genre = genre;
    this->duration = duration;
    this->playCount = playCount;
    this->likeCount = likeCount;
  }

  bool operator==(const Song& other) const { return id == other.id; }
  bool operator<(const Song& other) const { return id < other.id; }
  bool operator>(const Song& other) const { return id > other.id; }

  friend ostream& operator<<(ostream& os, const Song& s) {
    os << s.id << "|" << s.title << "|" << s.artist << "|" << s.genre << "|"
       << s.duration << "|" << s.playCount << "|" << s.likeCount;
    return os;
  }
};
