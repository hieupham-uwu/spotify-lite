#include "MusicLibrary.hpp"

MusicLibrary::MusicLibrary() : songsByID(211), songsByName(211) {}

void MusicLibrary::syncSongIndexes(const Song& song) {
  songsByID.insert(song.id, song);
  songsByName.insert(lowerStr(song.title), song);
}

void MusicLibrary::updateSongInAllSongs(const Song& song) {
  Song* found = allSongs.findData(song);
  if (found) {
    *found = song;
  }
}

bool MusicLibrary::loadFromFile(const string& fileName) {
  fstream f(fileName, ios::in);
  if (!f) {
    cout << "Can not open file songs \n";
    return false;
  }

  int numberOfLoadSong = 0;
  string str;

  while (getline(f, str)) {
    vector<string> loadedSong = trimString(str, '|');
    if (loadedSong.size() == 7) {
      Song song =
          Song(loadedSong[0], loadedSong[1], loadedSong[2], loadedSong[3],
               stoi(loadedSong[4]), stoi(loadedSong[5]), stoi(loadedSong[6]));
      addSong(song);
      numberOfLoadSong++;
    }
  }

  return numberOfLoadSong > 0;
}

bool MusicLibrary::saveToFile(const string& fileName) {
  fstream f(fileName, ios::out);
  if (!f) {
    cout << "Can not open file songs \n";
    return false;
  }
  vector<Song> songs = allSongs.toVector();
  for (auto& x : songs) {
    f << x << "\n";
  }

  return true;
}

void MusicLibrary::addSong(const Song& s) {
  if (!songsByID.contains(s.id)) {
    allSongs.insert(s);
    songCount++;
  } else {
    updateSongInAllSongs(s);
  }
  syncSongIndexes(s);
}

Song* MusicLibrary::findById(string id) {
  Song* findSong = songsByID.find(id);
  return findSong;
}

Song* MusicLibrary::findByTitle(string title) {
  Song* findSong = songsByName.find(lowerStr(title));
  return findSong;
}

bool MusicLibrary::increasePlayCount(string id) {
  Song* findSong = songsByID.find(id);
  if (findSong == nullptr) return false;
  findSong->playCount++;
  syncSongIndexes(*findSong);
  updateSongInAllSongs(*findSong);
  return true;
}

bool MusicLibrary::increaseLikeCount(string id) {
  Song* findSong = songsByID.find(id);
  if (findSong == nullptr) return false;
  findSong->likeCount++;
  syncSongIndexes(*findSong);
  updateSongInAllSongs(*findSong);
  return true;
}

const AVL<Song>& MusicLibrary::getAllSongs() const { return allSongs; }

vector<Song> MusicLibrary::getAllSongsVector() const {
  return allSongs.toVector();
}

int MusicLibrary::size() const { return songCount; }
