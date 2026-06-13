#ifndef CONSOLE_UI_HPP
#define CONSOLE_UI_HPP

#include <string>
#include <vector>
using namespace std;

#include "../services/ArtistManager.hpp"
#include "../services/MusicLibrary.hpp"
#include "../services/Player.hpp"
#include "../services/PlaylistManager.hpp"

class ConsoleUI {
 private:
  string filePath;
  string playlistPath;
  MusicLibrary library;
  PlaylistManager playlistManager;
  Player player;
  ArtistManager artistManager;

  struct MenuItem {
    int id;
    string title;
  };

  vector<MenuItem> menuItems;
  int selectedIndex;

  string getCurrentOS() const;

  // Các hàm tiện ích nhập xuất
  static int readInt(const string& prompt);
  static string readLine(const string& prompt);
  static int readNavigationKey();

  // Các hàm tiện ích vẽ giao diện
  static void clearScreen();
  static void pauseScreen();
  static string fitText(const string& text, int width);
  static string repeat(char ch, int count);
  static string centerText(const string& text, int width);
  static string progressBar(int percent, int width);

  // Vẽ layout
  void initMenuItems();
  void renderHome();
  void renderHeader() const;
  void renderSidebarAndPlayer() const;
  void renderFooter() const;
  void renderContentTitle(const string& title) const;
  void renderSongTable(const vector<Song>& songs, int limit = -1) const;
  vector<Song> getAllSongsVector() const;

  // Handlers - Tích hợp với Backend Services
  void handleShowAllSongs();
  void handleSearchById();
  void handleSearchByTitle();
  void handleCreatePlaylist();
  void handleDeletePlaylist();
  void handleShowAllPlaylists();
  void handleAddSongToPlaylist();
  void handleShowPlaylist();
  void handleRemoveSongFromPlaylist();
  void handleClearPlaylist();
  void handlePlayPlaylist();

  // Player Handlers
  void handleToggleShuffle();
  void handleNextSong();
  void handleBackSong();
  void handleLikeCurrentSong();

  // Ranking Handlers (Gọi RankingService)
  void handleTopByPlays();
  void handleTopByLikes();

  // Artist Handlers (Gọi ArtistManager)
  void handleShowArtistsAZ();
  void handleSearchSongsByArtist();

  // Recommendation Handlers (Gọi RecommendationService)
  void handleRecommendByGenre();
  void handleRecommendByCurrentSong();
  void handleHotSongsSuggestion();

  void dispatchSelectedItem();
  void rebuildIndexes();

 public:
  ConsoleUI();
  bool init(const string& dataFile, const string& playlistFile);
  void run();
};

#endif
