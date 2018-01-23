:WARNINGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wformat=2\
 -Winit-self -Wmissing-declarations -Wredundant-decls -Wshadow\
 -Wstrict-overflow=5 -Wswitch-default -Wundef

FLAGS = $(WARNINGS) -std=c++11

SRC = src/main.cpp

all: 
	g++ $(FLAGS) -Ofast $(SRC) -I include -o main
	./main

debug:
	g++ $(FLAGS) -DDEBUG $(SRC) -o main
	./main

