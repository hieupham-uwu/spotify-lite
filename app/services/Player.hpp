#pragma once
#include "../../lib/LINKEDLIST.hpp"
#include "../../lib/STACK.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

class Player {
 private:
  LINKEDLIST<Song> currentQueue;
  STACK<Song> history;
  int currentIndex;
  bool hasCurrent;
  Song currentSong;

  bool getSongAt(int index, Song& out) const;

 public:
  Player();

  void loadPlaylist(const LINKEDLIST<Song>& playlist);
  bool play(MusicLibrary& library);
  bool next(MusicLibrary& library);
  bool back(MusicLibrary& library);
  bool likeCurrentSong(MusicLibrary& library);

  bool getCurrentSong(Song& out) const;
  void showCurrentSong() const;
  void showQueue() const;
};
