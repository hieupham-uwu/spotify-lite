#pragma once;

#include <string>

#include "../../lib/LINKEDLIST.hpp"
#include "Song.hpp"

struct Artist {
  std::string name;
  LINKEDLIST<Song> songs;

  Artist();
  Artist(std::string name) { this->name; }

  bool operator<(const Artist& Other) const { return this->name < Other.name; }

  bool operator>(const Artist& Other) const { return this->name > Other.name; }

  bool operator==(const Artist& Other) const {
    return this->name == Other.name;
  }
};
