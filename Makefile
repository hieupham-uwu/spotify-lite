CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = spotify_lite.exe
    RM = del /f /q
    RUN = $(TARGET)
    FIX_PATH = $(subst /,\,$1)
else
    TARGET = spotify_lite
    RM = rm -f
    RUN = ./$(TARGET)
    FIX_PATH = $1
endif

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
	$(RM) $(call FIX_PATH,$(OBJS)) $(TARGET)

run: $(TARGET)
	$(RUN)