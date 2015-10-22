#include "puzzle_heur.h"
#include <cmath>

using namespace std;

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int total = 0;
	for(int i = 0; i<b.size(); i++)
	{
		if(b[i] != 0 && b[i] != i)
		{
			total++;
		}
	}
	return total;
}

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int sidedim = b.dim();
	int total = 0;
	for(int i=0; i<b.size(); i++)
	{
		if(b[i] != 0 && b[i] != i)
		{
			int wrongrow;
			int wrongcol;
			int rightrow;
			int rightcol;
			wrongrow = i / sidedim;
			wrongcol = i % sidedim;
			rightrow = b[i] / sidedim;
			rightcol = b[i] % sidedim;
			total += abs(rightrow-wrongrow);
			total += abs(rightcol-wrongcol);
		}
	}
	return total;
}