#ifndef RANKING_SERVICE_HPP
#define RANKING_SERVICE_HPP

#include <string>
#include <vector>

#include "../../lib/Algorithms.hpp"
#include "../../lib/LinkedList.hpp"
#include "../models/Song.hpp"
#include "MusicLibrary.hpp"

using namespace std;

class RankingService {
private:
    static vector<Song> getSongsAsVector(const MusicLibrary& library);

public:
    static LinkedList<Song> getTopByPlayCount(
        const MusicLibrary& library,
        int limit
    );

    static LinkedList<Song> getTopByLikeCount(
        const MusicLibrary& library,
        int limit
    );

    static LinkedList<Song> getTopByGenre(
        const MusicLibrary& library,
        const string& genre,
        int limit
    );
};

#endif
