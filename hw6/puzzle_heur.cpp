#include "puzzle_heur.h"
#include <cstdlib>


int PuzzleManhattanHeuristic::compute(const Board& b){
    //int cr =0, cc = 0, wr = 0, wc = 0;
    int dim = b.dim(), Dr = 0;
    for(int i = 0; i < dim*dim; i++){
      int yCurrent =  i%dim;
      int xCurrent = (i-yCurrent)/dim;
      int yDesired =  b[i] % dim;
      int xDesired = (b[i] - yDesired)/ dim; 
      Dr += abs(xCurrent - xDesired) + abs(yCurrent-yDesired);
    }
    return Dr;
  }

 int PuzzleOutOfPlaceHeuristic::compute(const Board& b){
    int displacement = 0;
    int dim = b.dim();
    for(int i = 0; i < dim*dim; i++){
      if(b[i] != i){
        displacement++;
      }
    }
    return displacement;
  }
 int PuzzleBFSHeuristic::compute(const Board& b){
    return 0;
  }