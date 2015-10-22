#include "puzzle_solver.h"
#include "heap.h"
using namespace std;



PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) :
	_b(b), _ph(ph)
{
	_expansions = 0;
}

PuzzleSolver::~PuzzleSolver()
{
}

std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}

int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}

void PuzzleSolver::run()
{
	bool finish = false;
	PuzzleMoveScoreComp movescore;
	PuzzleMoveSet closeList;
	Board* savetheBoard;
	savetheBoard = new Board(_b);
	PuzzleMove* move = new PuzzleMove(savetheBoard);
	PuzzleMove* final;
	Heap<PuzzleMove*,PuzzleMoveScoreComp> openList(2, movescore);
	closeList.insert(move);
	openList.push(move);
	while(!finish)
	{
		PuzzleMove* best = openList.top();
		openList.pop();
		if(best->b->solved())
		{
			final = best;
			finish = true;
			break;
		}
		map<int,Board*>potmoves = best->b->potentialMoves();
		for (map<int,Board*>::iterator it = potmoves.begin(); it!=potmoves.end(); ++it)
		{
			PuzzleMove* successor = new PuzzleMove(it->first,it->second,best);
			successor->h = _ph->compute(*(successor->b));
			PuzzleMoveSet::iterator lt = closeList.find(successor);
			if(lt == closeList.end())
			{
				closeList.insert(successor);
				openList.push(successor);
				_expansions++;		
			}
			else
			{	delete successor->b;
				delete successor;
			}
		}


	}
	while(final->prev != NULL)
	{	
		_solution.push_front(final->tileMove);
		final = final->prev;
	}
	for (PuzzleMoveSet::iterator mt = closeList.begin(); mt!=closeList.end(); ++mt)
	{
		delete (*mt)->b;
		delete (*mt); 
	}
}