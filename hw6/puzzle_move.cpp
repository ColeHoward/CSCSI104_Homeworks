#include "puzzle_move.h"

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent):b(board){
	PuzzleOutOfPlaceHeuristic displace;
    PuzzleManhattanHeuristic nyc;

    tileMove = tile;
    prev     = parent;
    g        = parent->g+1;
    
}
PuzzleMove::PuzzleMove(Board* board): b(board){
	g = 0;
	h = 0;
	tileMove = 0;

}
PuzzleMove::~PuzzleMove(){
	delete b;
}