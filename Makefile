FILE = $(wildcard *.cpp)
all:
	g++ --std=c++17 $(FILE) -o main -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_test -lSDL2_ttf -lSDL2_mixer