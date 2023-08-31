CXX = g++
CXXFLAGS = -Wall -std=c++11 -I$(PROJECT_DIR)/src/Include
LIBS = -lmingw32 -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -L$(PROJECT_DIR)/src/lib -lSDL2_image

PROJECT_DIR = .

SOURCES = main.cpp window.cpp game.cpp button.cpp

all: $(SOURCES)
	$(CXX) $(CXXFLAGS) -o main $^ $(LIBS)
