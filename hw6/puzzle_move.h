#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include "board.h"
#include "puzzle_heur.h"

//using namespace std;

struct PuzzleMove
{
  // Data members can be public
  int tileMove;  // tile moved to reach the Board b
  Board *b;      // Pointer to a board representing the updated state
  int g;         // distance from the start board
  int h;         // heuristic distance to the goal
  PuzzleMove *prev;  // Pointer to parent PuzzleMove


  // Constructor for starting Board (i.e. initial move)
  PuzzleMove(Board* board);
  /*
  //copy constructor for potential moves
  PuzzleMove(map<int, Board*> &potential, map<int, Board*>::iterator it,
                                                   PuzzleMove* previous){
      PuzzleOutOfPlaceHeuristic displace;
      PuzzleManhattanHeuristic nyc;

      b = it->second;
      tileMove = it->first;
      h = nyc.compute(*(it->second));
      g = displace.compute(*(it->second));
      prev = previous;
  }
  */

  // Constructor for subsequent search boards 
  // (i.e. those returned by Board::potentialMoves() )
  PuzzleMove(int tile, Board* board, PuzzleMove *parent);

  // Destructor
  ~PuzzleMove();

};


struct PuzzleMoveScoreComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    // Add code to check if m1's f-score is less than m2's
    // If both have the same f-score, break ties by 
    // checking if m1's h-score is less than m2's.
    // If both have the same f and same h score, break ties
    // by returning true when m1's tileMove is less than m2's.
    int f1 = m1->h + m1->g;
    int f2 = m2->h + m2->g;
    if(f1 < f2){
      return true;
    }
    else if(f1 == f2 and m1->h < m2->h){
      return true;
    }
    else if(f1 == f2 and m1->h == m2->h and m1->tileMove < m2->tileMove){
      return true;
    }
    else{
      return false;
    }
  }
};

struct PuzzleMoveBoardComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    // Add code to check if m1's board is "less-than" m2's board by 
    // using the Board class' operator<()
    return *(m1->b) < *(m2->b);
  }
};

#endif