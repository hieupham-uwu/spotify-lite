CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = spotify_lite.exe
    RM = del /f /q
    RUN = $(TARGET)
    FIX_PATH = $(subst /,\,$1)
    
    WINDRES = windres
    RES_OBJ = resource.o
else
    TARGET = spotify_lite
    RM = rm -f
    RUN = ./$(TARGET)
    FIX_PATH = $1
    
    RES_OBJ = 
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

$(TARGET): $(OBJS) $(RES_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(RES_OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ifeq ($(OS),Windows_NT)
$(RES_OBJ): resource.rc
	$(WINDRES) $< -O coff -o $@
endif

clean:
	$(RM) $(call FIX_PATH,$(OBJS)) $(TARGET) $(RES_OBJ)

run: $(TARGET)
	$(RUN)