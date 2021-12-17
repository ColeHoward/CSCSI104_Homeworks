CC = g++
CFLAGS = -g -Wall -std=c++11

all: puzzle board.o puzzle_move.o puzzle_heur.o puzzle_solver.o

puzzle: puzzle.cpp board.o puzzle_move.o puzzle_heur.o puzzle_solver.o
	$(CC) $(CFLAGS) puzzle.cpp board.o puzzle_move.o puzzle_heur.o puzzle_solver.o -o puzzle

board.o: board.cpp board.h
	$(CC) $(CFLAGS) -c board.cpp -o board.o

puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h board.o puzzle_move.o puzzle_heur.o
	$(CC) $(CFLAGS) -c puzzle_solver.cpp -o puzzle_solver.o

puzzle_move.o: puzzle_move.cpp puzzle_move.h board.o
	$(CC) $(CFLAGS) -c puzzle_move.cpp -o puzzle_move.o

puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h board.o
	$(CC) $(CFLAGS) -c puzzle_heur.cpp -o puzzle_heur.o


clean:
	rm -f puzzle *.o