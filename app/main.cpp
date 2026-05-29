#include <iostream>

#include "ui/ConsoleUI.hpp"

int main() {
  ConsoleUI app;
  std::string dataPath = "app/data/songs.txt";

  std::cout << "=========================================\n";
  std::cout << "      INITIALIZING SPOTIFY LITE...       \n";
  std::cout << "=========================================\n";

  if (!app.init(dataPath)) {
    std::cout << "\n[!] Warning: Could not load song data from: " << dataPath
              << "\n";
    std::cout << "    Please verify the file path and format.\n";
    std::cout << "    Press ENTER to continue with an empty library...";
    std::cin.get();
  }

  app.run();

  return 0;
}