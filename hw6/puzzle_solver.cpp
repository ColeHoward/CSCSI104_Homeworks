#include "puzzle_solver.h"
#include "heap.h"
#include <iostream>
#include <deque>

//SOMETHING IS WRONG WITH SETTING THE PREV*

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph):b_(b),ph_(ph){
	expansions_ = 0;
}
 PuzzleSolver::~PuzzleSolver(){

 }
void PuzzleSolver::setSolution(PuzzleMove* moves){
	if(moves->prev == nullptr) return;
	
	solution_.push_front(moves->tileMove);
	setSolution(moves->prev);
}
deque<int> PuzzleSolver::getSolution(){
	return solution_;
}

int PuzzleSolver::getNumExpansions(){
	return expansions_;
}

//inspiration for implementation from slides
void PuzzleSolver:: run(){
	PuzzleMoveScoreComp PMSC;
	PuzzleMoveBoardComp PMBC;
	Heap<PuzzleMove*, PuzzleMoveScoreComp> openList(2, PMSC);
	PuzzleMoveSet closedList(PMBC); 

	Board* parent = new Board(b_);
	PuzzleMove* start = new PuzzleMove(parent);
	start->h = ph_->compute(*parent);

	openList.push(start);
	//closedList.insert(start);
	while(!openList.empty()){
		PuzzleMove* topPuzz = openList.top();
		//update heuristc
		openList.pop();
		closedList.insert(topPuzz);

		if(topPuzz->b->solved()){
			this->setSolution(topPuzz);
			break;
		}
		map<int, Board*> moves = topPuzz->b->potentialMoves();

		map<int, Board*>::iterator it;

		for(it = moves.begin(); it != moves.end(); ++it){
			PuzzleMove* manyWorlds = new PuzzleMove(it->first, it->second, 
																  topPuzz);
			manyWorlds->h = ph_->compute(*(it->second));
			if(closedList.find(manyWorlds) == closedList.end()){
				openList.push(manyWorlds);
				expansions_++;
				//expansions_ = count2;
			}
			else{
				int manyF    = manyWorlds->g + manyWorlds->h;
				int compareF = (*closedList.find(manyWorlds))->g 
							 +	(*closedList.find(manyWorlds))->h;

				if(manyF < compareF){
					(*closedList.find(manyWorlds))->g = manyWorlds->g;
					(*closedList.find(manyWorlds))->h = manyWorlds->h;
				}
			}
			//delete manyWorlds;
		}
	}
}
