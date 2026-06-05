#ifndef PLAYLIST_MANAGER_HPP
#define PLAYLIST_MANAGER_HPP

#include <string>

#include "../../lib/HashTable.hpp"
#include "../../lib/LinkedList.hpp"
#include "../models/Playlist.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

using namespace std;

class PlaylistManager {
private:
    HashTable<string, Playlist> playlists;
    LinkedList<string> playlistNames;

    string normalizeName(const string& name) const;

public:
    PlaylistManager();

    bool createPlaylist(const string& playlistName);
    bool deletePlaylist(const string& playlistName);
    bool hasPlaylist(const string& playlistName) const;

    Playlist* findPlaylist(const string& playlistName);
    const Playlist* findPlaylist(const string& playlistName) const;

    bool addSongToPlaylist(
        const string& playlistName,
        const string& songId,
        MusicLibrary& library
    );

    bool removeSongFromPlaylist(
        const string& playlistName,
        const string& songId
    );

    bool clearPlaylist(const string& playlistName);

    LinkedList<string> getAllPlaylistNames() const;
    int playlistCount() const;
};

#endif
