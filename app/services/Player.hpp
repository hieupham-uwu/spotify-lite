#pragma once
#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

#include "../../lib/LINKEDLIST.hpp"
#include "../../lib/STACK.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

class Player {
 private:
  std::vector<Song*> originalQueue;
  std::vector<Song*> playbackQueue;
  STACK<Song*> history;

  Song* currentSong;
  int currentIndex;
  bool isShuffle;

  void applyShuffle();

 public:
  Player();

  void loadPlaylist(const LINKEDLIST<Song*>& playlist);

  bool play(MusicLibrary& library);
  bool next(MusicLibrary& library);
  bool back(MusicLibrary& library);
  bool likeCurrentSong(MusicLibrary& library);

  void toggleShuffle();

  void showCurrentSong() const;
  void showQueue() const;
};