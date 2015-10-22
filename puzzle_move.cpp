#include "puzzle_move.h"

using namespace std;


PuzzleMove::PuzzleMove(Board* board)
{
	tileMove = -1;
	b = board;
	g = 0;
	h = 0;
	prev = NULL;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
  	tileMove = tile;
  	b = board;
  	prev = parent;
  	h = 0;
  	g = prev->g + 1;
}

PuzzleMove::~PuzzleMove()
{

}
