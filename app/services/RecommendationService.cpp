#include "RecommendationService.hpp"
#include "../utilities/StringUtils.hpp"

using namespace std;

// ==========================
// SongScore
// ==========================

SongScore::SongScore() {
    this->score = 0;
}

SongScore::SongScore(const Song& song, int score) {
    this->song = song;
    this->score = score;
}

bool SongScore::operator<(const SongScore& other) const {
    if(score != other.score){
    	return score < other.score;
	}
	
	return song.title > other.song.title;
}

bool SongScore::operator>(const SongScore& other) const {
    if(score != other.score){
    	return score > other.score;
	}
	
	return song.title < other.song.title;
}


// ==========================
// RecommendationService helper
// ==========================

int RecommendationService::calculateHotScore(const Song& song) {
    return song.playCount * 2 + song.likeCount * 3;
}


// ==========================
// Recommend hot songs
// ==========================

LINKEDLIST<Song> RecommendationService::recommendHotSongs(
    const MusicLibrary& library,
    int limit
) {
    LINKEDLIST<Song> result;

    if(limit <= 0) return result;

    vector<Song> songs = library.getAllSongsVector();

    PRIORITYQUEUE<SongScore> pq;

    for(Song& song : songs){
    	int score = calculateHotScore(song);
    	SongScore s(song,score);
    	pq.push(s);
	}

    int count = 0;
    
    while(!pq.empty() && count < limit){
    	SongScore topSong = pq.top();
    	pq.pop();
    	result.push_back(topSong.song);
    	count++;
	}

    return result;
}


// ==========================
// Recommend songs by genre
// ==========================

LINKEDLIST<Song> RecommendationService::recommendByGenre(
    const MusicLibrary& library,
    const string& genre,
    int limit
) {
    LINKEDLIST<Song> result;

    if(limit <= 0 || genre.empty()) return result;

    vector<Song> songs = library.getAllSongsVector();

    string genreKey = lowerStr(genre);

    PRIORITYQUEUE<SongScore> pq;

    for(Song& song : songs){
    	if(lowerStr(song.genre) == genreKey){
    	    int score = calculateHotScore(song);
        	SongScore s(song,score);
    	    pq.push(s);
		}
	}

    int count = 0;
    
    while(!pq.empty() && count < limit){
    	SongScore topSong = pq.top();
    	pq.pop();
    	result.push_back(topSong.song);
    	count++;
	}

    return result;
}


// ==========================
// Recommend similar songs
// ==========================

LINKEDLIST<Song> RecommendationService::recommendSimilarSongs(
    MusicLibrary& library,
    const string& currentSongId,
    int limit
) {
    LINKEDLIST<Song> result;

    if(limit <= 0 || currentSongId.empty()) return result;

    Song* currentSong = library.findById(currentSongId);

    if(currentSong == NULL) return result;

    string genreKey = lowerStr(currentSong->genre);

    vector<Song> songs = library.getAllSongsVector();

    PRIORITYQUEUE<SongScore> pq;

    for(Song& song : songs){
    	if(song.id == currentSongId) continue;
		if(lowerStr(song.genre) == genreKey){
    	    int score = calculateHotScore(song);
        	SongScore s(song,score);
    	    pq.push(s);
		}
	}

    int count = 0;
    
    while(!pq.empty() && count < limit){
    	SongScore topSong = pq.top();
    	pq.pop();
    	result.push_back(topSong.song);
    	count++;
	}

    return result;
}
