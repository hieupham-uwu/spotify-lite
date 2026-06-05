#ifndef ARTIST_MANAGER_HPP
#define ARTIST_MANAGER_HPP

#include <string>
#include <vector>

#include "../../lib/AVL.hpp"
#include "../../lib/HashTable.hpp"
#include "../../lib/LinkedList.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

using namespace std;

class ArtistManager {
private:
    AVL<string> artistTree;
    HashTable<string, string> displayArtistNames;
    HashTable<string, LinkedList<string>> songsByArtist;

    string normalizeArtistName(const string& artistName) const;

public:
    ArtistManager();

    void buildFromLibrary(const MusicLibrary& library);

    bool hasArtist(const string& artistName) const;

    LinkedList<string> getArtistsAZ() const;

    LinkedList<string> getSongIdsByArtist(const string& artistName) const;

    int artistCount() const;

    void clear();
};

#endif
