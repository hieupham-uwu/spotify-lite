#include "Player.hpp"

#include <iostream>

#include "../utilities/StringUtils.hpp"

Player::Player() {
  currentIndex = 0;
  currentSong = nullptr;
  isShuffle = false;
}

void Player::loadPlaylist(const LINKEDLIST<Song*>& playlist) {
  originalQueue.clear();
  playbackQueue.clear();

  for (auto song : playlist) {
    originalQueue.push_back(song);
  }

  playbackQueue = originalQueue;
  history.clear();
  currentIndex = 0;
  isShuffle = false;

  if (!playbackQueue.empty()) {
    currentSong = playbackQueue[0];
  } else {
    currentSong = nullptr;
  }

  cout << "Loaded " << playbackQueue.size() << " songs into the queue.\n";
}

void Player::toggleShuffle() {
  if (originalQueue.empty()) return;

  isShuffle = !isShuffle;

  if (isShuffle) {
    cout << "Shuffle is ON.\n";
    applyShuffle();
  } else {
    cout << "Shuffle is OFF.\n";
    playbackQueue = originalQueue;

    for (size_t i = 0; i < playbackQueue.size(); i++) {
      if (playbackQueue[i]->id == currentSong->id) {
        currentIndex = i;
        break;
      }
    }
  }
}

void Player::applyShuffle() {
  if (playbackQueue.empty() || currentSong == nullptr) return;

  Song* playingNow = playbackQueue[currentIndex];

  srand(time(0));
  for (int i = playbackQueue.size() - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(playbackQueue[i], playbackQueue[j]);
  }

  for (size_t i = 0; i < playbackQueue.size(); i++) {
    if (playbackQueue[i]->id == playingNow->id) {
      swap(playbackQueue[0], playbackQueue[i]);
      break;
    }
  }
  currentIndex = 0;
}

bool Player::play(MusicLibrary& library) {
  if (playbackQueue.empty() || currentSong == nullptr) return false;
  library.increasePlayCount(currentSong->id);
  showCurrentSong();
  return true;
}

bool Player::next(MusicLibrary& library) {
  if (playbackQueue.empty()) return false;

  if (currentSong != nullptr) {
    history.push(currentSong);
  }

  currentIndex = (currentIndex + 1) % playbackQueue.size();
  currentSong = playbackQueue[currentIndex];

  return play(library);
}

bool Player::back(MusicLibrary& library) {
  if (history.empty()) {
    cout << "No song in the history!\n";
    return false;
  }

  currentSong = history.top();
  history.pop();

  for (size_t i = 0; i < playbackQueue.size(); i++) {
    if (playbackQueue[i]->id == currentSong->id) {
      currentIndex = i;
      break;
    }
  }

  library.increasePlayCount(currentSong->id);
  showCurrentSong();
  return true;
}

bool Player::likeCurrentSong(MusicLibrary& library) {
  if (currentSong == nullptr) return false;
  library.increaseLikeCount(currentSong->id);
  return true;
}

void Player::showCurrentSong() const {
  if (currentSong == nullptr) {
    cout << "No song is currently playing.\n";
    return;
  }
  cout << "\nNow playing: " << currentSong->title << " - "
       << currentSong->artist << " [" << currentSong->genre << ", "
       << formatDuration(currentSong->duration) << "]\n";
}

void Player::showQueue() const {
  cout << "\n========== CURRENT QUEUE ==========" << "\n";
  if (playbackQueue.empty()) {
    cout << "Queue is empty.\n";
    return;
  }

  int idx = 1;
  for (Song* song : playbackQueue) {
    if (song->id == currentSong->id) {
      cout << "=> ";
    } else {
      cout << "   ";
    }

    cout << idx++ << ". " << song->title << " - " << song->artist << " ("
         << formatDuration(song->duration) << ")\n";
  }
}

Song* Player::getCurrentSong() const { return currentSong; }
bool Player::getShuffleState() const { return isShuffle; }