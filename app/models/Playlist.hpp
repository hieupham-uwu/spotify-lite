#pragma once;

#include <string>

#include "../../lib/LINKEDLIST.hpp"
#include "Song.hpp"

struct Playlist {
  std::string name;
  LINKEDLIST<Song> songs;
  Playlist();
  Playlist(std::string name) { this->name = name; }
};