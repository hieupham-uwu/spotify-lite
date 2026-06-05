#pragma once

#include <string>

#include "../../lib/LinkedList.hpp"
#include "Song.hpp"
using namespace std;

struct Artist {
  std::string name;
  LinkedList<Song> songs;

  Artist();
  Artist(std::string name) { this->name = name; }

  bool operator<(const Artist& Other) const { return this->name < Other.name; }

  bool operator>(const Artist& Other) const { return this->name > Other.name; }

  bool operator==(const Artist& Other) const {
    return this->name == Other.name;
  }
};
