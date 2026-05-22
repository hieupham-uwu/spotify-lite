#include "ArtistManager.hpp"
#include "../utilities/StringUtils.hpp"

using namespace std;

// ==========================
// Helper
// ==========================

string ArtistManager::normalizeArtistName(const string& artistName) const {
    return lowerStr(artistName);
}


// ==========================
// Constructor
// ==========================

ArtistManager::ArtistManager()
    : displayArtistNames(211), songsByArtist(211) {
}


// ==========================
// Build data from MusicLibrary
// ==========================

void ArtistManager::buildFromLibrary(const MusicLibrary& library) {
    clear();
    
    vector<Song> Songs = library.getAllSongsVector();
    for(Song &s : Songs){
    	string key = normalizeArtistName(s.artist);
    	if(key.empty()) continue;
    	if(!artistTree.search(key)){
    		artistTree.insert(key);
    		displayArtistNames.insert(key,s.artist);
    		LINKEDLIST<string> List;
    		songsByArtist.insert(key,List);
		}
		LINKEDLIST<string>* ListSong = songsByArtist.find(key);
		if(ListSong != NULL && ListSong->find(s.id) == ListSong->end()){
			ListSong->push_back(s.id);
		}
	}
	
}


// ==========================
// Check artist exists
// ==========================

bool ArtistManager::hasArtist(const string& artistName) const {
    if(artistName.empty()) return false;
    
    string key = normalizeArtistName(artistName);
    return artistTree.search(key);
}


// ==========================
// Get artists A-Z
// ==========================

LINKEDLIST<string> ArtistManager::getArtistsAZ() const {
    LINKEDLIST<string> result;

    vector<string> Artist = artistTree.inorder();
    for(string &s : Artist){
    	const string* displayName = displayArtistNames.find(s);
    	if(displayName != NULL){
    		result.push_back(*displayName);
		}
	}

    return result;
}


// ==========================
// Get song IDs by artist
// ==========================

LINKEDLIST<string> ArtistManager::getSongIdsByArtist(
    const string& artistName
) const {
    LINKEDLIST<string> result;

    if(artistName.empty()) return result;
    string key = normalizeArtistName(artistName);
    const LINKEDLIST<string>* songList = songsByArtist.find(key);
    if(songList != NULL) result = *songList;

    return result;
}


// ==========================
// Count artists
// ==========================

int ArtistManager::artistCount() const {
    vector<string> artists = artistTree.inorder();
    return (int)artists.size();
}

// ==========================
// Clear all data
// ==========================

void ArtistManager::clear() {
    
    artistTree.clear();
    displayArtistNames.clear();
    songsByArtist.clear();
}
