#include "ConsoleUI.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "../services/RankingService.hpp"
#include "../services/RecommendationService.hpp"
#include "../utilities/StringUtils.hpp"

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

namespace {
const int SCREEN_W = 106;
const int SIDE_W = 34;
const int RIGHT_W = SCREEN_W - SIDE_W - 3;
}  // namespace

ConsoleUI::ConsoleUI() : selectedIndex(0) { initMenuItems(); }

string ConsoleUI::getCurrentOS() const {
#ifdef _WIN32
  return "Windows";
#elif __APPLE__
  return "macOS";
#elif __linux__
  return "Linux";
#else
  return "Unknown OS";
#endif
}

bool ConsoleUI::init(const string& dataFile) {
  filePath = dataFile;
  playlistPath = "app/data/playlists.txt";

  bool ok = library.loadFromFile(dataFile);

  playlistManager.loadFromFile(playlistPath, library);

  rebuildIndexes();
  return ok;
}

void ConsoleUI::rebuildIndexes() {
  // ArtistManager tự động trích xuất nghệ sĩ từ MusicLibrary
  artistManager.buildFromLibrary(library);
}

void ConsoleUI::initMenuItems() {
  menuItems.clear();
  menuItems.push_back({1, "Library: Show all songs"});
  menuItems.push_back({2, "Search song by ID"});
  menuItems.push_back({3, "Search song by title"});
  menuItems.push_back({4, "Create playlist"});
  menuItems.push_back({5, "Show all playlists"});
  menuItems.push_back({6, "Add song to playlist"});
  menuItems.push_back({7, "Show playlist details"});
  menuItems.push_back({8, "Remove song from playlist"});
  menuItems.push_back({9, "Play playlist"});
  menuItems.push_back({10, "Toggle Shuffle"});
  menuItems.push_back({11, "Next song"});
  menuItems.push_back({12, "Previous song"});
  menuItems.push_back({13, "Like current song"});
  menuItems.push_back({14, "Ranking: Top plays"});
  menuItems.push_back({15, "Ranking: Top likes"});
  menuItems.push_back({16, "Artists: A-Z List"});
  menuItems.push_back({17, "Artists: Songs by Artist"});
  menuItems.push_back({18, "Discover: By Genre"});
  menuItems.push_back({19, "Discover: Similar to playing"});
  menuItems.push_back({20, "Discover: Hot Songs"});
  menuItems.push_back({0, "Exit"});
}

void ConsoleUI::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void ConsoleUI::pauseScreen() {
  cout << "\n  Press ENTER to return to menu...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}

string ConsoleUI::repeat(char ch, int count) { return string(count, ch); }

string ConsoleUI::fitText(const string& text, int width) {
  if (width <= 0) return "";
  if ((int)text.size() <= width) return text + string(width - text.size(), ' ');
  if (width <= 3) return text.substr(0, width);
  return text.substr(0, width - 3) + "...";
}

string ConsoleUI::centerText(const string& text, int width) {
  if ((int)text.size() >= width) return fitText(text, width);
  int left = (width - (int)text.size()) / 2;
  int right = width - (int)text.size() - left;
  return string(left, ' ') + text + string(right, ' ');
}

string ConsoleUI::progressBar(int percent, int width) {
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  int filled = width * percent / 100;
  return "[" + string(filled, '=') + string(width - filled, '-') + "]";
}

int ConsoleUI::readInt(const string& prompt) {
  int value;
  while (true) {
    cout << prompt;
    if (cin >> value) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return value;
    }
    cout << "  Invalid number. Try again.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

string ConsoleUI::readLine(const string& prompt) {
  string s;
  cout << prompt;
  getline(cin, s);
  return s;
}

int ConsoleUI::readNavigationKey() {
#ifdef _WIN32
  int ch = _getch();
  if (ch == 224 || ch == 0) {
    int arrow = _getch();
    if (arrow == 72) return -1;  // up
    if (arrow == 80) return 1;   // down
    return 999;
  }
  if (ch == 13) return 0;     // enter
  if (ch == 27) return 1000;  // esc
  if (ch == 'q' || ch == 'Q') return 1000;
  return 999;
#else
  cout << "\n[W: Up | S: Down | E: Enter | Q: Quit] : ";
  char ch;
  cin >> ch;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (ch == 'w' || ch == 'W') return -1;
  if (ch == 's' || ch == 'S') return 1;
  if (ch == 'e' || ch == 'E') return 0;
  if (ch == 'q' || ch == 'Q') return 1000;
  return 999;
#endif
}

void ConsoleUI::renderHeader() const {
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
  cout << "|" << centerText("SPOTIFY LITE - C++ TERMINAL EDITION", SCREEN_W - 2)
       << "|\n";
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
}

void ConsoleUI::renderSidebarAndPlayer() const {
  cout << "+" << repeat('-', SIDE_W) << "+" << repeat('-', RIGHT_W) << "+\n";
  cout << "|" << fitText("  MENU", SIDE_W) << "|"
       << fitText("  MINI PLAYER DASHBOARD", RIGHT_W) << "|\n";
  cout << "+" << repeat('-', SIDE_W) << "+" << repeat('-', RIGHT_W) << "+\n";

  int rows = max((int)menuItems.size(), 13);
  Song* current = player.getCurrentSong();

  for (int i = 0; i < rows; ++i) {
    string left;
    if (i < (int)menuItems.size()) {
      ostringstream os;
      os << (i == selectedIndex ? " > " : "   ");
      os << setw(2) << menuItems[i].id << ". " << menuItems[i].title;
      left = os.str();
    }

    string right;
    if (i == 0)
      right = "  NOW PLAYING";
    else if (i == 2 && current)
      right = "  [" + current->id + "] " + current->title;
    else if (i == 3 && current)
      right = "  " + current->artist + " | " + current->genre;
    else if (i == 4 && current) {
      right = "  Plays: " + to_string(current->playCount) +
              "   Likes: " + to_string(current->likeCount);
    } else if (i == 5 && current) {
      string shuffleStatus = player.getShuffleState() ? "ON" : "OFF";
      right = "  Shuffle: " + shuffleStatus;
    } else if (i == 7 && current) {
      right = "  " + progressBar(45, 30) + "  " +
              formatDuration(current->duration / 2) + " / " +
              formatDuration(current->duration);
    } else if (i == 2 && !current)
      right = "  No song is currently playing";
    else if (i == 3 && !current)
      right = "  Create a playlist and press Play!";

    else if (i == 10)
      right = "  " + repeat('-', RIGHT_W - 4);
    else if (i == 11)
      right = "  Controls:";
    else if (i == 12) {
      string opS = getCurrentOS();
      if (opS == "Windows") {
        right = "  [Up/Down] Navigate";
      } else
        right = "  [W/S] Navigate";
    } else if (i == 13) {
      string opS = getCurrentOS();
      if (opS == "Windows") {
        right = "  [Enter] Select";
      } else
        right = "  [E] Select";
    }

    cout << "|" << fitText(left, SIDE_W) << "|" << fitText(right, RIGHT_W)
         << "|\n";
  }
  cout << "+" << repeat('-', SIDE_W) << "+" << repeat('-', RIGHT_W) << "+\n";
}

void ConsoleUI::renderFooter() const {
  cout << "|" << centerText("Student Project - HieuPham UWU", SCREEN_W - 2)
       << "|\n";
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
}

void ConsoleUI::renderHome() {
  clearScreen();
  renderHeader();
  renderSidebarAndPlayer();
  renderFooter();
}

void ConsoleUI::renderContentTitle(const string& title) const {
  clearScreen();
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
  cout << "|" << centerText(title, SCREEN_W - 2) << "|\n";
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
}

void ConsoleUI::renderSongTable(const vector<Song>& songs, int limit) const {
  if (songs.empty()) {
    cout << "  No songs to display.\n";
    return;
  }

  int count = (limit < 0) ? (int)songs.size() : min(limit, (int)songs.size());
  cout << "+-----+--------+--------------------------+----------------------+--"
          "----------+-------+-------+\n";
  cout << "| No  | ID     | Title                    | Artist               | "
          "Genre      | Plays | Likes |\n";
  cout << "+-----+--------+--------------------------+----------------------+--"
          "----------+-------+-------+\n";

  for (int i = 0; i < count; ++i) {
    cout << "| " << setw(3) << right << i + 1 << " "
         << "| " << left << setw(6) << fitText(songs[i].id, 6) << " | " << left
         << setw(24) << fitText(songs[i].title, 24) << " | " << left << setw(20)
         << fitText(songs[i].artist, 20) << " | " << left << setw(10)
         << fitText(songs[i].genre, 10) << " | " << right << setw(5)
         << songs[i].playCount << " | " << right << setw(5)
         << songs[i].likeCount << " |\n";
  }
  cout << "+-----+--------+--------------------------+----------------------+--"
          "----------+-------+-------+\n";
}

vector<Song> ConsoleUI::getAllSongsVector() const {
  return library.getAllSongsVector();
}

// ================= HANDLERS =================

void ConsoleUI::handleShowAllSongs() {
  renderContentTitle("LIBRARY - ALL SONGS");
  renderSongTable(getAllSongsVector());
  pauseScreen();
}

void ConsoleUI::handleSearchById() {
  renderContentTitle("SEARCH SONG BY ID");
  string id = readLine("  Enter song ID: ");
  Song* song = library.findById(id);
  if (song)
    renderSongTable({*song});
  else
    cout << "  Song not found.\n";
  pauseScreen();
}

void ConsoleUI::handleSearchByTitle() {
  renderContentTitle("SEARCH SONG BY TITLE");
  string title = readLine("  Enter song title: ");
  Song* song = library.findByTitle(title);
  if (song)
    renderSongTable({*song});
  else
    cout << "  Song not found.\n";
  pauseScreen();
}

void ConsoleUI::handleCreatePlaylist() {
  renderContentTitle("CREATE PLAYLIST");

  string name = readLine("  Enter playlist name: ");

  if (playlistManager.createPlaylist(name)) {
    cout << "  Playlist created successfully.\n";
    playlistManager.saveToFile(playlistPath);
  } else {
    cout << "  Cannot create playlist. Name may be empty, invalid, or already "
            "exists.\n";
  }

  pauseScreen();
}

void ConsoleUI::handleShowAllPlaylists() {
  renderContentTitle("YOUR PLAYLISTS");
  LinkedList<string> names = playlistManager.getAllPlaylistNames();
  if (names.empty()) {
    cout << "  No playlists found.\n";
  } else {
    int idx = 1;
    for (auto name : names) {
      cout << "  " << idx++ << ". " << name << "\n";
    }
  }
  pauseScreen();
}

void ConsoleUI::handleAddSongToPlaylist() {
  string playlistName = "";
  string songId = "";

  while (true) {
    clearScreen();

    cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
    cout << "|" << centerText("ADD SONG TO PLAYLIST", SCREEN_W - 2) << "|\n";
    cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";

    int leftW = 45;
    int rightW = SCREEN_W - leftW - 3;

    cout << "|" << fitText("  ACTIONS & INPUT", leftW) << "|"
         << fitText("  REFERENCE LISTS", rightW) << "|\n";
    cout << "+" << repeat('-', leftW) << "+" << repeat('-', rightW) << "+\n";

    LinkedList<string> playlists = playlistManager.getAllPlaylistNames();
    LinkedList<Song> topSongs = RankingService::getTopByPlayCount(library, 5);

    vector<string> leftLines = {
        "",
        "  [1] Enter Playlist Name: ",
        "      => " + (playlistName.empty() ? "<EMPTY>" : playlistName),
        "",
        "  [2] Enter Song ID: ",
        "      => " + (songId.empty() ? "<EMPTY>" : songId),
        "",
        "  [S] Submit / Add Song",
        "  [0] Cancel / Back"};

    vector<string> rightLines;

    rightLines.push_back("  --- YOUR PLAYLISTS ---");
    if (playlists.empty()) {
      rightLines.push_back("  (No playlists found)");
    } else {
      int idx = 1;
      for (string name : playlists) {
        if (idx > 6) {
          rightLines.push_back("  ... and more");
          break;
        }
        rightLines.push_back("  " + to_string(idx++) + ". " + name);
      }
    }

    rightLines.push_back("");

    rightLines.push_back("  --- POPULAR SONGS ---");
    if (topSongs.empty()) {
      rightLines.push_back("  (No songs found)");
    } else {
      int idx = 1;
      for (Song s : topSongs) {
        string songDisplay = fitText(s.title, 25);
        rightLines.push_back("  " + to_string(idx++) + ". " + songDisplay +
                             " (ID: " + s.id + ")");
      }
    }

    int maxLines = max((int)leftLines.size(), (int)rightLines.size());
    maxLines = max(maxLines, 12);

    for (int i = 0; i < maxLines; ++i) {
      string l = (i < (int)leftLines.size()) ? leftLines[i] : "";
      string r = (i < (int)rightLines.size()) ? rightLines[i] : "";
      cout << "|" << fitText(l, leftW) << "|" << fitText(r, rightW) << "|\n";
    }
    cout << "+" << repeat('-', leftW) << "+" << repeat('-', rightW) << "+\n";

    string choice = readLine("\n  Enter your choice: ");

    if (choice == "0") {
      break;
    } else if (choice == "1") {
      playlistName = readLine("  -> Input Playlist Name: ");
    } else if (choice == "2") {
      songId = readLine("  -> Input Song ID: ");
    } else if (choice == "s" || choice == "S") {
      if (playlistName.empty() || songId.empty()) {
        cout << "  Error: Playlist Name and Song ID cannot be empty.\n";
        pauseScreen();
      } else {
        if (playlistManager.addSongToPlaylist(playlistName, songId, library)) {
          if (playlistManager.saveToFile(playlistPath)) {
            cout << "  Success: Song added successfully!\n";
          } else {
            cout << "  Song added, but failed to save playlist file.\n";
          }
          songId = "";
        } else {
          cout << "  Error: Failed to add song. Check if playlist exists and "
                  "Song ID is correct.\n";
        }
        pauseScreen();
      }
    } else {
      cout << "  Invalid choice. Please try again.\n";
      pauseScreen();
    }
  }
}

void ConsoleUI::handleShowPlaylist() {
  renderContentTitle("SHOW PLAYLIST DETAILS");
  string name = readLine("  Playlist name: ");
  const Playlist* p = playlistManager.findPlaylist(name);

  if (!p) {
    cout << "  Playlist not found.\n";
  } else {
    vector<Song> songs;
    for (auto id : p->songIds) {
      Song* s = library.findById(id);
      if (s) songs.push_back(*s);
    }
    cout << "\n  Playlist: " << p->name << " (" << p->size() << " songs)\n";
    renderSongTable(songs);
  }
  pauseScreen();
}

void ConsoleUI::handleRemoveSongFromPlaylist() {
  renderContentTitle("REMOVE SONG");
  string name = readLine("  Playlist name: ");
  string id = readLine("  Song ID to remove: ");

  if (playlistManager.removeSongFromPlaylist(name, id)) {
    cout << "  Song removed.\n";
    playlistManager.saveToFile(playlistPath);
  } else {
    cout << "  Cannot remove song. Check playlist name or Song ID.\n";
  }

  pauseScreen();
}

void ConsoleUI::handleClearPlaylist() {
  renderContentTitle("CLEAR PLAYLIST");
  string name = readLine("  Playlist name: ");

  if (playlistManager.clearPlaylist(name)) {
    cout << "  Playlist cleared.\n";
    playlistManager.saveToFile(playlistPath);
  } else {
    cout << "  Playlist not found.\n";
  }

  pauseScreen();
}

void ConsoleUI::handlePlayPlaylist() {
  renderContentTitle("PLAY PLAYLIST");
  string name = readLine("  Playlist name: ");
  Playlist* p = playlistManager.findPlaylist(name);

  if (!p || p->empty()) {
    cout << "  Playlist not found or empty.\n";
    pauseScreen();
    return;
  }

  // Convert LinkedList<string> (ID) to LinkedList<Song*>
  LinkedList<Song*> songQueue;
  for (string id : p->songIds) {
    Song* s = library.findById(id);
    if (s) songQueue.insertBack(s);
  }

  player.loadPlaylist(songQueue);
  if (player.play(library)) {
    cout << "\n  Started playing playlist: " << name << "\n";
    library.saveToFile(filePath);
  }
  pauseScreen();
}

void ConsoleUI::handleToggleShuffle() {
  renderContentTitle("TOGGLE SHUFFLE");
  player.toggleShuffle();
  pauseScreen();
}

void ConsoleUI::handleNextSong() {
  renderContentTitle("NEXT SONG");
  if (player.next(library)) {
    cout << "  Skipped to next song.\n";
    library.saveToFile(filePath);
  } else {
    cout << "  Cannot skip (Queue is empty).\n";
  }
  pauseScreen();
}

void ConsoleUI::handleBackSong() {
  renderContentTitle("PREVIOUS SONG");
  if (player.back(library)) {
    cout << "  Returned to previous song.\n";
    library.saveToFile(filePath);
  } else {
    cout << "  No history found.\n";
  }
  pauseScreen();
}

void ConsoleUI::handleLikeCurrentSong() {
  renderContentTitle("LIKE CURRENT SONG");
  if (player.likeCurrentSong(library)) {
    cout << "  You liked: " << player.getCurrentSong()->title << "!\n";
    library.saveToFile(filePath);
  } else {
    if (player.getCurrentSong() != nullptr) {
      cout << "  You have already liked: " << player.getCurrentSong()->title
           << ".\n";
    } else {
      cout << "  No song is currently playing.\n";
    }
  }
  pauseScreen();
}

void ConsoleUI::handleTopByPlays() {
  renderContentTitle("RANKING - TOP 10 BY PLAYS");
  LinkedList<Song> topList = RankingService::getTopByPlayCount(library, 10);
  vector<Song> vec;
  for (Song s : topList) vec.push_back(s);
  renderSongTable(vec);
  pauseScreen();
}

void ConsoleUI::handleTopByLikes() {
  renderContentTitle("RANKING - TOP 10 BY LIKES");
  LinkedList<Song> topList = RankingService::getTopByLikeCount(library, 10);
  vector<Song> vec;
  for (Song s : topList) vec.push_back(s);
  renderSongTable(vec);
  pauseScreen();
}

void ConsoleUI::handleShowArtistsAZ() {
  renderContentTitle("ALL ARTISTS (A-Z)");
  LinkedList<string> artists = artistManager.getArtistsAZ();
  int idx = 1;
  for (string name : artists) {
    cout << "  " << idx++ << ". " << name << "\n";
  }
  pauseScreen();
}

void ConsoleUI::handleSearchSongsByArtist() {
  renderContentTitle("SEARCH SONGS BY ARTIST");

  LinkedList<string> artists = artistManager.getArtistsAZ();

  cout << "  AVAILABLE ARTISTS (A-Z)\n";
  cout << "  +----+------------------------------+\n";
  cout << "  | No | Artist                       |\n";
  cout << "  +----+------------------------------+\n";

  int index = 1;
  for (string artist : artists) {
    cout << "  | " << setw(2) << right << index++ << " "
         << "| " << left << setw(28) << fitText(artist, 28) << " |\n";
  }

  cout << "  +----+------------------------------+\n\n";

  string name = readLine("  Artist name: ");
  LinkedList<string> songIds = artistManager.getSongIdsByArtist(name);

  if (songIds.empty()) {
    cout << "\n  No songs found for artist: " << name << "\n";
  } else {
    vector<Song> vec;

    for (string id : songIds) {
      Song* s = library.findById(id);

      if (s) {
        vec.push_back(*s);
      }
    }

    cout << "\n";
    renderSongTable(vec);
  }

  pauseScreen();
}
void ConsoleUI::handleRecommendByGenre() {
  renderContentTitle("DISCOVER BY GENRE");
  string genre = readLine("  Enter Genre (e.g. Pop, EDM): ");
  LinkedList<Song> recs =
      RecommendationService::recommendByGenre(library, genre, 10);

  vector<Song> vec;
  for (Song s : recs) vec.push_back(s);
  renderSongTable(vec);
  pauseScreen();
}

void ConsoleUI::handleRecommendByCurrentSong() {
  renderContentTitle("DISCOVER - SIMILAR TO PLAYING");
  Song* curr = player.getCurrentSong();
  if (!curr) {
    cout << "  Play a song first to get recommendations!\n";
  } else {
    LinkedList<Song> recs =
        RecommendationService::recommendSimilarSongs(library, curr->id, 10);
    vector<Song> vec;
    for (Song s : recs) vec.push_back(s);

    cout << "\n  Because you are listening to " << curr->title << " ("
         << curr->genre << "):\n\n";
    renderSongTable(vec);
  }
  pauseScreen();
}

void ConsoleUI::handleHotSongsSuggestion() {
  renderContentTitle("DISCOVER - HOTTEST TRENDING SONGS");
  LinkedList<Song> recs = RecommendationService::recommendHotSongs(library, 10);
  vector<Song> vec;
  for (Song s : recs) vec.push_back(s);

  cout << "  Trending score = (Plays * 2) + (Likes * 3)\n\n";
  renderSongTable(vec);
  pauseScreen();
}

void ConsoleUI::dispatchSelectedItem() {
  int id = menuItems[selectedIndex].id;
  switch (id) {
    case 1:
      handleShowAllSongs();
      break;
    case 2:
      handleSearchById();
      break;
    case 3:
      handleSearchByTitle();
      break;
    case 4:
      handleCreatePlaylist();
      break;
    case 5:
      handleShowAllPlaylists();
      break;
    case 6:
      handleAddSongToPlaylist();
      break;
    case 7:
      handleShowPlaylist();
      break;
    case 8:
      handleRemoveSongFromPlaylist();
      break;
    case 9:
      handlePlayPlaylist();
      break;
    case 10:
      handleToggleShuffle();
      break;
    case 11:
      handleNextSong();
      break;
    case 12:
      handleBackSong();
      break;
    case 13:
      handleLikeCurrentSong();
      break;
    case 14:
      handleTopByPlays();
      break;
    case 15:
      handleTopByLikes();
      break;
    case 16:
      handleShowArtistsAZ();
      break;
    case 17:
      handleSearchSongsByArtist();
      break;
    case 18:
      handleRecommendByGenre();
      break;
    case 19:
      handleRecommendByCurrentSong();
      break;
    case 20:
      handleHotSongsSuggestion();
      break;
    case 0:
      selectedIndex = (int)menuItems.size() - 1;
      break;
    default:
      break;
  }
}

void ConsoleUI::run() {
  while (true) {
    renderHome();
    int key = readNavigationKey();

#ifndef _WIN32
    if (key >= 2000) {
      int choice = key - 2000;
      bool found = false;
      for (size_t i = 0; i < menuItems.size(); ++i) {
        if (menuItems[i].id == choice) {
          selectedIndex = (int)i;
          found = true;
          break;
        }
      }
      if (!found) continue;
      if (choice == 0) break;
      dispatchSelectedItem();
      continue;
    }
#endif

    if (key == -1) {
      selectedIndex--;
      if (selectedIndex < 0) selectedIndex = (int)menuItems.size() - 1;
    } else if (key == 1) {
      selectedIndex++;
      if (selectedIndex >= (int)menuItems.size()) selectedIndex = 0;
    } else if (key == 0) {
      if (menuItems[selectedIndex].id == 0) break;
      dispatchSelectedItem();
    } else if (key == 1000) {
      break;
    }
  }

  clearScreen();
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
  cout << "|"
       << centerText("Goodbye! Thanks for using Spotify Lite.", SCREEN_W - 2)
       << "|\n";
  cout << "+" << repeat('-', SCREEN_W - 2) << "+\n";
}
