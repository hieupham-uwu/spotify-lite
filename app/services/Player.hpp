#pragma once
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "../../lib/LinkedList.hpp"
#include "../../lib/Stack.hpp"
#include "../models/Song.hpp"
#include "../utilities/StringUtils.hpp"
#include "MusicLibrary.hpp"

using namespace std;
class Player {
 private:
  vector<Song*> originalQueue;
  vector<Song*> playbackQueue;
  Stack<Song*> history;

  Song* currentSong;
  int currentIndex;
  bool isShuffle;

  void applyShuffle();

 public:
  Player();

  void loadPlaylist(const LinkedList<Song*>& playlist);

  bool play(MusicLibrary& library);
  bool next(MusicLibrary& library);
  bool back(MusicLibrary& library);
  bool likeCurrentSong(MusicLibrary& library);

  void toggleShuffle();

  void showCurrentSong() const;
  void showQueue() const;

  Song* getCurrentSong() const;
  bool getShuffleState() const;
};