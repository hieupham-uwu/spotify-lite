#ifndef RECOMMENDATION_SERVICE_HPP
#define RECOMMENDATION_SERVICE_HPP

#include <string>
#include <vector>

#include "../../lib/LinkedList.hpp"
#include "../../lib/PriorityQueue.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

using namespace std;

struct SongScore {
    Song song;
    int score;

    SongScore();
    SongScore(const Song& song, int score);

    bool operator<(const SongScore& other) const;
    bool operator>(const SongScore& other) const;
};

class RecommendationService {
private:
    static int calculateHotScore(const Song& song);

public:
    static LinkedList<Song> recommendHotSongs(
        const MusicLibrary& library,
        int limit
    );

    static LinkedList<Song> recommendByGenre(
        const MusicLibrary& library,
        const string& genre,
        int limit
    );

    static LinkedList<Song> recommendSimilarSongs(
        MusicLibrary& library,
        const string& currentSongId,
        int limit
    );
};

#endif
