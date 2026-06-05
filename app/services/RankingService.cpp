#include "RankingService.hpp"

#include "../utilities/StringUtils.hpp"

using namespace std;

vector<Song> RankingService::getSongsAsVector(const MusicLibrary& library) {
    return library.getAllSongsVector();
}

LinkedList<Song> RankingService::getTopByPlayCount(
    const MusicLibrary& library,
    int limit
) {
    LinkedList<Song> res;

    if (limit <= 0) {
        return res;
    }

    vector<Song> songs = getSongsAsVector(library);

    if (songs.empty()) {
        return res;
    }

    heapSort(songs, [](const Song& a, const Song& b) {
        if (a.playCount != b.playCount) {
            return a.playCount > b.playCount;
        }

        return a.title < b.title;
    });

    int count = limit;

    if (count > (int)songs.size()) {
        count = (int)songs.size();
    }

    for (int i = 0; i < count; i++) {
        res.insertBack(songs[i]);
    }

    return res;
}

LinkedList<Song> RankingService::getTopByLikeCount(
    const MusicLibrary& library,
    int limit
) {
    LinkedList<Song> res;

    if (limit <= 0) {
        return res;
    }

    vector<Song> songs = getSongsAsVector(library);

    if (songs.empty()) {
        return res;
    }

    heapSort(songs, [](const Song& a, const Song& b) {
        if (a.likeCount != b.likeCount) {
            return a.likeCount > b.likeCount;
        }

        return a.title < b.title;
    });

    int count = limit;

    if (count > (int)songs.size()) {
        count = (int)songs.size();
    }

    for (int i = 0; i < count; i++) {
        res.insertBack(songs[i]);
    }

    return res;
}

LinkedList<Song> RankingService::getTopByGenre(
    const MusicLibrary& library,
    const string& genre,
    int limit
) {
    LinkedList<Song> res;

    if (limit <= 0 || genre.empty()) {
        return res;
    }

    vector<Song> songs = getSongsAsVector(library);

    if (songs.empty()) {
        return res;
    }

    vector<Song> filteredSongs;
    string genreKey = lowerStr(genre);

    for (Song& s : songs) {
        if (lowerStr(s.genre) == genreKey) {
            filteredSongs.push_back(s);
        }
    }

    if (filteredSongs.empty()) {
        return res;
    }

    heapSort(filteredSongs, [](const Song& a, const Song& b) {
        if (a.playCount != b.playCount) {
            return a.playCount > b.playCount;
        }

        if (a.likeCount != b.likeCount) {
            return a.likeCount > b.likeCount;
        }

        return a.title < b.title;
    });

    int count = limit;

    if (count > (int)filteredSongs.size()) {
        count = (int)filteredSongs.size();
    }

    for (int i = 0; i < count; i++) {
        res.insertBack(filteredSongs[i]);
    }

    return res;
}
