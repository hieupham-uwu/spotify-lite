CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = spotify_lite.exe

SRCS = app/main.cpp \
       app/services/MusicLibrary.cpp \
       app/services/Player.cpp \
       app/services/PlaylistManager.cpp \
       app/services/ArtistManager.cpp \
       app/services/RankingService.cpp \
       app/services/RecommendationService.cpp \
       app/utilities/StringUtils.cpp \
       app/ui/ConsoleUI.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /f /q $(subst /,\,$(OBJS)) 2>nul & exit 0
	if exist $(TARGET) del /f /q $(TARGET)

run: $(TARGET)
	$(TARGET)