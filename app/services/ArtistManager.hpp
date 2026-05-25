#ifndef ARTIST_MANAGER_HPP
#define ARTIST_MANAGER_HPP

#include <string>
#include <vector>

#include "../../lib/AVL.hpp"
#include "../../lib/HASHTABLE.hpp"
#include "../../lib/LINKEDLIST.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

using namespace std;

class ArtistManager {
private:
    AVL<string> artistTree;
    HashTable<string, string> displayArtistNames;
    HashTable<string, LINKEDLIST<string>> songsByArtist;

    string normalizeArtistName(const string& artistName) const;

public:
    ArtistManager();

    void buildFromLibrary(const MusicLibrary& library);

    bool hasArtist(const string& artistName) const;

    LINKEDLIST<string> getArtistsAZ() const;

    LINKEDLIST<string> getSongIdsByArtist(const string& artistName) const;

    int artistCount() const;

    void clear();
};

#endif
