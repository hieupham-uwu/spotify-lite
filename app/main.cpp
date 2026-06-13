#include <iostream>
using namespace std;
#include "ui/ConsoleUI.hpp"

int main() {
  ConsoleUI app;
  string dataPath = "app/data/songs.txt";
  string playlistPath = "app/data/playlists.txt";

  cout << "=========================================\n";
  cout << "      INITIALIZING SPOTIFY LITE...       \n";
  cout << "=========================================\n";

  if (!app.init(dataPath, playlistPath)) {
    cout << "\n[!] Warning: Could not load song data from: " << dataPath
         << "\n";
    cout << "    Please verify the file path and format.\n";
    cout << "    Press ENTER to continue with an empty library...";
    cin.get();
  }

  app.run();

  return 0;
}