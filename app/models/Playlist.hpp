#pragma once

#include <string>
#include "../../lib/LINKEDLIST.hpp"

using namespace std;

struct Playlist {
    string name;
    LINKEDLIST<string> songIds;

    Playlist() {
        name = "";
    }

    Playlist(string name) {
        this->name = name;
    }

    bool addSongId(const string& songId) {
        if (songId.empty()) {
            return false;
        }

        if (containsSongId(songId)) {
            return false;
        }

        songIds.push_back(songId);
        return true;
    }

    bool removeSongId(const string& songId) {
        auto it = songIds.find(songId);

        if (it == songIds.end()) {
            return false;
        }

        songIds.erase(it);
        return true;
    }

    bool containsSongId(const string& songId) const {
        auto it = songIds.find(songId);
        return it != songIds.end();
    }

    void clear() {
        songIds.clear();
    }

    int size() const {
        return (int)songIds.size();
    }

    bool empty() const {
        return songIds.empty();
    }
};
