#include "PlaylistManager.hpp"

#include <cctype>
#include <fstream>
#include <sstream>

#include "../utilities/StringUtils.hpp"
using namespace std;

string PlaylistManager::normalizeName(const string& name) const {
  string result = normalizeDisplayName(name);

  for (int i = 0; i < (int)result.length(); i++) {
    result[i] = (char)tolower((unsigned char)result[i]);
  }

  return result;
}

PlaylistManager::PlaylistManager() {}

bool PlaylistManager::createPlaylist(const string& playlistName) {
  string cleanName = normalizeDisplayName(playlistName);

  if (cleanName.empty() || cleanName.find('|') != string::npos) {
    return false;
  }

  string key = normalizeName(cleanName);

  if (playlists.contains(key)) {
    return false;
  }

  Playlist newPlaylist(cleanName);

  playlists.insert(key, newPlaylist);
  playlistNames.insertBack(cleanName);

  return true;
}

bool PlaylistManager::deletePlaylist(const string& playlistName) {
  if (playlistName.empty()) {
    return false;
  }

  string key = normalizeName(playlistName);

  if (!playlists.contains(key)) {
    return false;
  }

  playlists.remove(key);

  for (auto it = playlistNames.begin(); it != playlistNames.end(); ++it) {
    if (normalizeName(*it) == key) {
      playlistNames.removeIt(it);
      break;
    }
  }

  return true;
}

bool PlaylistManager::hasPlaylist(const string& playlistName) const {
  if (playlistName.empty()) {
    return false;
  }

  string key = normalizeName(playlistName);
  return playlists.contains(key);
}

Playlist* PlaylistManager::findPlaylist(const string& playlistName) {
  if (playlistName.empty()) {
    return nullptr;
  }

  string key = normalizeName(playlistName);
  return playlists.find(key);
}

const Playlist* PlaylistManager::findPlaylist(
    const string& playlistName) const {
  if (playlistName.empty()) {
    return nullptr;
  }

  string key = normalizeName(playlistName);
  return playlists.find(key);
}

bool PlaylistManager::addSongToPlaylist(const string& playlistName,
                                        const string& songId,
                                        MusicLibrary& library) {
  if (playlistName.empty() || songId.empty()) {
    return false;
  }

  Playlist* playlist = findPlaylist(playlistName);

  if (playlist == nullptr) {
    return false;
  }

  Song* song = library.findById(songId);

  if (song == nullptr) {
    return false;
  }

  return playlist->addSongId(songId);
}

bool PlaylistManager::removeSongFromPlaylist(const string& playlistName,
                                             const string& songId) {
  if (playlistName.empty() || songId.empty()) {
    return false;
  }

  Playlist* playlist = findPlaylist(playlistName);

  if (playlist == nullptr) {
    return false;
  }

  return playlist->removeSongId(songId);
}

bool PlaylistManager::clearPlaylist(const string& playlistName) {
  if (playlistName.empty()) {
    return false;
  }

  Playlist* playlist = findPlaylist(playlistName);

  if (playlist == nullptr) {
    return false;
  }

  playlist->clear();
  return true;
}

LinkedList<string> PlaylistManager::getAllPlaylistNames() const {
  return playlistNames;
}

int PlaylistManager::playlistCount() const { return playlistNames.size(); }
bool PlaylistManager::loadFromFile(const string& fileName,
                                   MusicLibrary& library) {
  fstream f(fileName, ios::in);

  if (!f) {
    return false;
  }

  string line;
  int loadedCount = 0;

  while (getline(f, line)) {
    if (line.empty()) {
      continue;
    }

    stringstream ss(line);
    string playlistName;

    getline(ss, playlistName, '|');
    playlistName = normalizeDisplayName(playlistName);
    if (playlistName.empty()) {
      continue;
    }

    if (!hasPlaylist(playlistName)) {
      createPlaylist(playlistName);
    }

    string songId;

    while (getline(ss, songId, '|')) {
      if (!songId.empty() && library.findById(songId) != nullptr) {
        addSongToPlaylist(playlistName, songId, library);
      }
    }

    loadedCount++;
  }

  return loadedCount > 0;
}

bool PlaylistManager::saveToFile(const string& fileName) const {
  fstream f(fileName, ios::out);

  if (!f) {
    return false;
  }

  for (string playlistName : playlistNames) {
    const Playlist* playlist = findPlaylist(playlistName);

    if (playlist == nullptr) {
      continue;
    }

    f << playlist->name;

    for (string songId : playlist->songIds) {
      f << "|" << songId;
    }

    f << "\n";
  }

  return true;
}
