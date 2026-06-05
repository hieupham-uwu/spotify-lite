#include "ArtistManager.hpp"

#include "../utilities/StringUtils.hpp"

using namespace std;

string ArtistManager::normalizeArtistName(const string& artistName) const {
    return lowerStr(artistName);
}

ArtistManager::ArtistManager()
    : displayArtistNames(211), songsByArtist(211) {
}

void ArtistManager::buildFromLibrary(const MusicLibrary& library) {
    clear();

    vector<Song> songs = library.getAllSongsVector();

    for (Song& s : songs) {
        string key = normalizeArtistName(s.artist);

        if (key.empty()) {
            continue;
        }

        if (!artistTree.search(key)) {
            artistTree.insert(key);
            displayArtistNames.insert(key, s.artist);

            LinkedList<string> list;
            songsByArtist.insert(key, list);
        }

        LinkedList<string>* listSong = songsByArtist.find(key);

        if (listSong != nullptr && listSong->find(s.id) == listSong->end()) {
            listSong->insertBack(s.id);
        }
    }
}

bool ArtistManager::hasArtist(const string& artistName) const {
    if (artistName.empty()) {
        return false;
    }

    string key = normalizeArtistName(artistName);
    return artistTree.search(key);
}

LinkedList<string> ArtistManager::getArtistsAZ() const {
    LinkedList<string> result;

    vector<string> artists = artistTree.inorder();

    for (string& s : artists) {
        const string* displayName = displayArtistNames.find(s);

        if (displayName != nullptr) {
            result.insertBack(*displayName);
        }
    }

    return result;
}

LinkedList<string> ArtistManager::getSongIdsByArtist(
    const string& artistName
) const {
    LinkedList<string> result;

    if (artistName.empty()) {
        return result;
    }

    string key = normalizeArtistName(artistName);

    const LinkedList<string>* songList = songsByArtist.find(key);

    if (songList != nullptr) {
        result = *songList;
    }

    return result;
}

int ArtistManager::artistCount() const {
    vector<string> artists = artistTree.inorder();
    return (int)artists.size();
}

void ArtistManager::clear() {
    artistTree.clear();
    displayArtistNames.clear();
    songsByArtist.clear();
}
