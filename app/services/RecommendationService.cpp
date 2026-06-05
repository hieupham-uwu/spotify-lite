#include "RecommendationService.hpp"

#include "../utilities/StringUtils.hpp"

using namespace std;

SongScore::SongScore() {
    this->score = 0;
}

SongScore::SongScore(const Song& song, int score) {
    this->song = song;
    this->score = score;
}

bool SongScore::operator<(const SongScore& other) const {
    if (score != other.score) {
        return score < other.score;
    }

    return song.title > other.song.title;
}

bool SongScore::operator>(const SongScore& other) const {
    if (score != other.score) {
        return score > other.score;
    }

    return song.title < other.song.title;
}

int RecommendationService::calculateHotScore(const Song& song) {
    return song.playCount * 2 + song.likeCount * 3;
}

LinkedList<Song> RecommendationService::recommendHotSongs(
    const MusicLibrary& library,
    int limit
) {
    LinkedList<Song> result;

    if (limit <= 0) {
        return result;
    }

    vector<Song> songs = library.getAllSongsVector();

    PriorityQueue<SongScore> pq;

    for (Song& song : songs) {
        int score = calculateHotScore(song);
        SongScore songScore(song, score);
        pq.insert(songScore);
    }

    int count = 0;

    while (!pq.empty() && count < limit) {
        SongScore topSong = pq.extract();
        result.insertBack(topSong.song);
        count++;
    }

    return result;
}

LinkedList<Song> RecommendationService::recommendByGenre(
    const MusicLibrary& library,
    const string& genre,
    int limit
) {
    LinkedList<Song> result;

    if (limit <= 0 || genre.empty()) {
        return result;
    }

    vector<Song> songs = library.getAllSongsVector();

    string genreKey = lowerStr(genre);

    PriorityQueue<SongScore> pq;

    for (Song& song : songs) {
        if (lowerStr(song.genre) == genreKey) {
            int score = calculateHotScore(song);
            SongScore songScore(song, score);
            pq.insert(songScore);
        }
    }

    int count = 0;

    while (!pq.empty() && count < limit) {
        SongScore topSong = pq.extract();
        result.insertBack(topSong.song);
        count++;
    }

    return result;
}

LinkedList<Song> RecommendationService::recommendSimilarSongs(
    MusicLibrary& library,
    const string& currentSongId,
    int limit
) {
    LinkedList<Song> result;

    if (limit <= 0 || currentSongId.empty()) {
        return result;
    }

    Song* currentSong = library.findById(currentSongId);

    if (currentSong == nullptr) {
        return result;
    }

    string genreKey = lowerStr(currentSong->genre);

    vector<Song> songs = library.getAllSongsVector();

    PriorityQueue<SongScore> pq;

    for (Song& song : songs) {
        if (song.id == currentSongId) {
            continue;
        }

        if (lowerStr(song.genre) == genreKey) {
            int score = calculateHotScore(song);
            SongScore songScore(song, score);
            pq.insert(songScore);
        }
    }

    int count = 0;

    while (!pq.empty() && count < limit) {
        SongScore topSong = pq.extract();
        result.insertBack(topSong.song);
        count++;
    }

    return result;
}
