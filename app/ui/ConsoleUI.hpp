#ifndef CONSOLE_UI_HPP
#define CONSOLE_UI_HPP

#include <string>
#include <vector>

#include "../services/ArtistManager.hpp"
#include "../services/MusicLibrary.hpp"
#include "../services/Player.hpp"
#include "../services/PlaylistManager.hpp"

class ConsoleUI {
 private:
  MusicLibrary library;
  PlaylistManager playlistManager;
  Player player;
  ArtistManager artistManager;

  struct MenuItem {
    int id;
    std::string title;
  };

  std::vector<MenuItem> menuItems;
  int selectedIndex;

  // Các hàm tiện ích nhập xuất
  static int readInt(const std::string& prompt);
  static std::string readLine(const std::string& prompt);
  static int readNavigationKey();

  // Các hàm tiện ích vẽ giao diện
  static void clearScreen();
  static void pauseScreen();
  static std::string fitText(const std::string& text, int width);
  static std::string repeat(char ch, int count);
  static std::string centerText(const std::string& text, int width);
  static std::string progressBar(int percent, int width);

  // Vẽ layout
  void initMenuItems();
  void renderHome();
  void renderHeader() const;
  void renderSidebarAndPlayer() const;
  void renderFooter() const;
  void renderContentTitle(const std::string& title) const;
  void renderSongTable(const std::vector<Song>& songs, int limit = -1) const;
  std::vector<Song> getAllSongsVector() const;

  // Handlers - Tích hợp với Backend Services
  void handleShowAllSongs();
  void handleSearchById();
  void handleSearchByTitle();
  void handleCreatePlaylist();
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
  bool init(const std::string& dataFile);
  void run();
};

#endif