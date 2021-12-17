#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];                                 
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& b){
  size_ = b.size();
  tiles_ = new int[size_];
  for(int i = 0; i < size_; i++){
    tiles_[i] = b[i];
  }
}
Board::~Board(){
  delete [] tiles_; 
}

void Board::move(int tile)
{
  int side_dim = this->dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1; 
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j= -1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    stringstream ss;
    ss << "Invalid move of tile " << tile << " at ";
    ss << tr << "," << tc << " and blank spot at ";
    ss << br << "," << bc << endl;
    throw BoardMoveError(ss.str());
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  int blank = 0;
  for(int i = 0; i < size_; i++){
    if(tiles_[i] == 0){
      blank = i;
      break;
    }
  }
  map<int, Board*> mgh;
  Board* board1 = new Board(*this);
  Board* board2 = new Board(*this);
  Board* board3 = new Board(*this);
  Board* board4 = new Board(*this);
  //top row
  int dim = this->dim();

  if(blank < dim){
    //standard case
    if(blank != 0 and blank != dim-1){
      //down
      board1->move(tiles_[blank+dim]);
      mgh[ tiles_[blank+dim] ] = board1;
      //left
      board2->move(tiles_[blank-1]);
      mgh[ tiles_[blank-1] ]   = board2;
      //right
      board3->move(tiles_[blank+1]);
      mgh[ tiles_[blank+1] ] = board3;
      delete board4;
    }
    //top left corner
    else if(blank == 0){
      //down
      board1->move(tiles_[blank+dim]);
      mgh[ tiles_[blank+dim] ] = board1;
      //right
      board2->move((*board2)[blank+1]);
      mgh[ tiles_[blank+1] ] = board2;

      delete board3;
      delete board4;
    }
    //top right corner
    else if(blank == dim-1){
      //down
      board1->move(tiles_[blank+dim]);
      mgh[ tiles_[blank+dim] ] = board1;
      //left
      board2->move(tiles_[blank-1]);
      mgh[ tiles_[blank-1] ]   = board2;

      delete board3;
      delete board4;
    }
  }
  //bottom row
  else if(blank >= size_-dim and blank < size_){
    //bottom left corner
    if(blank == size_-dim){
      //right
      board1->move(tiles_[blank+1]);
      mgh[ tiles_[blank+1] ] = board1;
      //up
      board2->move(tiles_[blank-dim]);
      mgh[ tiles_[blank-dim] ] = board2;

      delete board3;
      delete board4;
    }
    //bottom right corner
    else if(blank == size_-1){
      //left
      board1->move(tiles_[blank-1]);
      mgh[ tiles_[blank-1] ]   = board1;
      //up
      board2->move(tiles_[blank-dim]);
      mgh[ tiles_[blank-dim] ] = board2;

      delete board3;
      delete board4;
    }
    //standard cases
    else{
      //left
      board1->move(tiles_[blank-1]);
      mgh[ tiles_[blank-1] ]   = board1;
      //right
      board2->move(tiles_[blank+1]);
      mgh[ tiles_[blank+1] ] = board2;
      //up
      board3->move(tiles_[blank-dim]);
      mgh[ tiles_[blank-dim] ] = board3;

      delete board4;
    }
  }
  //first column
  else if(blank% dim == 0){
    //down
    board1->move(tiles_[blank+dim]);
    mgh[ tiles_[blank+dim] ] = board1;
    //right
    board2->move(tiles_[blank+1]);
    mgh[ tiles_[blank+1] ] = board2;
    //up 
    board3->move(tiles_[blank-dim]);
    mgh[ tiles_[blank-dim] ] = board3;

    delete board4;
  }
  //last column
  else if( (blank+1)% dim == 0){
    //down
    board1->move(tiles_[blank+dim]);
    mgh[ tiles_[blank+dim] ] = board1;
    //left
    board2->move(tiles_[blank-1]);
    mgh[ tiles_[blank-1] ] = board2;    
    //up
    board3->move(tiles_[blank-dim]);
    mgh[ tiles_[blank-dim] ] = board3;

    delete board4;
  }
  //everything else
  else{
    //down
    board1->move(tiles_[blank+dim]);
    mgh[ tiles_[blank+dim] ] = board1;
    //left
    board2->move(tiles_[blank-1]);
    mgh[ tiles_[blank-1] ]   = board2;
    //right
    board3->move(tiles_[blank+1]);
    mgh[ tiles_[blank+1] ] = board3;
    //up
    board4->move(tiles_[blank-dim]);
    mgh[ tiles_[blank-dim] ] = board4;
  }
  return mgh;
}

// Complete this function
bool Board::solved() const
{

  for(int i = 0; i < size_; i++){
    if(tiles_[i] != i){
      return false;
    }
  }
  return true;
}


const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
std::ostream& operator<<(std::ostream &os, const Board &b){
  int dim = b.dim();
  b.printRowBanner(os);
  for(int i = 0; i < dim*dim; i++){
    if(i%dim == 0 and i != 0){
      os << "|" << "\n";
      b.printRowBanner(os);
    }
    if(b[i] == 0){
      os << "|" << "  ";
    }
    else{
      os << "|" << setw(2) << b[i];
    }
  }
  os << "|" << "\n";
  b.printRowBanner(os);
  return os;
}

  // Checks if this board is less-than another.  
  // We define less than as a "string-style" comparison 
  // of the tile array (i.e. Starting by comparing
  // the 0-th tile in this Board and the other.
  // If this board's tile is less than the other board's
  // tile value, return true. If they are equal,
  // continue with the next tile location and repeat).

bool Board::operator<(const Board& rhs) const{
  for(int i = 0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
      return true;
    }
    else if (tiles_[i] > rhs.tiles_[i]){
      return false;
    }
  }
  return false;

}