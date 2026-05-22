#include "PlaylistManager.hpp"
#include <cctype>

using namespace std;

string PlaylistManager::normalizeName(const string& name) const {
    string result = name;

    for (int i = 0; i < (int)result.length(); i++) {
        result[i] = tolower(result[i]);
    }

    return result;
}

PlaylistManager::PlaylistManager() {
}

bool PlaylistManager::createPlaylist(const string& playlistName) {
    if (playlistName.empty()) {
        return false;
    }

    string key = normalizeName(playlistName);

    if (playlists.contains(key)) {
        return false;
    }

    Playlist newPlaylist(playlistName);

    playlists.insert(key, newPlaylist);
    playlistNames.push_back(playlistName);

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
            playlistNames.erase(it);
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

const Playlist* PlaylistManager::findPlaylist(const string& playlistName) const {
    if (playlistName.empty()) {
        return nullptr;
    }

    string key = normalizeName(playlistName);
    return playlists.find(key);
}

bool PlaylistManager::addSongToPlaylist(
    const string& playlistName,
    const string& songId,
    MusicLibrary& library
) {
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

bool PlaylistManager::removeSongFromPlaylist(
    const string& playlistName,
    const string& songId
) {
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

LINKEDLIST<string> PlaylistManager::getAllPlaylistNames() const {
    return playlistNames;
}

int PlaylistManager::playlistCount() const {
    return (int)playlistNames.size();
}
