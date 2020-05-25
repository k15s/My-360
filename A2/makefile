CC = g++
# CFLAGS = -O3 -std=c++0x -pg -D_DEBUG -g -c -Wall
# CFLAGS = -O3 -std=c++0x -g -Wall
CFLAGS = -O3
EXEC = PuzzleGenerator

all:
	$(CC) $(CFLAGS) -o $(EXEC) main.cpp Puzzle.cpp CustomTuple.cpp

clean:
	rm -f $(EXEC)

test:
	make clean
	make all
	./$(EXEC) 5 5 2 4
