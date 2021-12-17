#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  int dim = atoi(argv[1]), initMoves = atoi(argv[2]), seed = atoi(argv[3]), 
     heur = atoi(argv[4]);

  Board* board = new Board(dim, initMoves, seed);

  PuzzleHeuristic* heuristic;
  if(heur == 0){
  	heuristic = new PuzzleBFSHeuristic;
  }
  else if(heur == 1){
  	heuristic = new PuzzleOutOfPlaceHeuristic;
  }
  else if(heur == 2){
  	heuristic = new PuzzleManhattanHeuristic;
  }
  else{
  	cout << "Invalid heuristic" << endl;
  	return -1;
  }
  int move = -2;

  while(move != 0){
  	cout << *board << endl;
  	cout << "Enter tile number to move or -1 for a cheat: ";
  	cin  >> move;
  	if(move == 0){
  		delete heuristic;
      delete board;
  	  return 1;
  	}
  	//cheat
  	else if(move == -1){
  		PuzzleSolver puzzle(*board, heuristic);
  		puzzle.run();
      cout << "Try this sequence: ";
  		int expansion       = puzzle.getNumExpansions();
      deque<int> solution = puzzle.getSolution();

  		for(int i = 0; i < (int)solution.size(); i++){
  			cout << solution[i] << " ";
  		}
  		cout << endl << "(Expansions = " << expansion << ")" << endl;

  	}
  	else{
  		try{
        board->move(move);
      }
      catch(BoardMoveError& error){
        cerr << error.what() << endl;
      }
  		if(board->solved()){
  			cout << *board << endl;
  			delete heuristic;
        delete board;
  			return 1;
  		}
  	}
  }

  return 0;
}