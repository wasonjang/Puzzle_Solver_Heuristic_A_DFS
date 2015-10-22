#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  int n;
  int initMoves;
  int seed;
  int heur;
  PuzzleHeuristic* ph;
  n = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);
  heur = atoi(argv[4]);
  Board* b = new Board(n, initMoves, seed);
  if(heur == 0)
  {
  	ph = new PuzzleBFSHeuristic;
  }
  else if(heur == 1)
  {
  	ph = new PuzzleOutOfPlaceHeuristic;
  }
  else if(heur == 2)
  {
  	ph = new PuzzleManhattanHeuristic;
  }
  else
  {
  	cerr<<"Invalid Heuristic"<<endl;
  	return 1;
  }
  while(!(b->solved()))
  {
  	cout << *b <<endl;
  	cout <<"Enter title number to move or -1 for a cheat: ";
  	int number;
  	cin >> number;
  	if(number > 0 && number < n*n )
  	{
  		b->move(number);
  	}
  	else if(number == -1)
  	{
  		
  		PuzzleSolver* p = new PuzzleSolver(*b, ph);
  		p->run();
  		deque<int>d = p->getSolution();
  		cout << "Try This sequence:"<<endl;
  		for(unsigned int i=0; i<d.size(); i++)
  		{
  			cout << d[i] <<" ";
  		}
  		cout<<"(Expansions = " << p->getNumExpansions() <<")"<<endl;
  		delete p;
  	}
  	else if (number == 0)
  	{
  		break;
  	}
  }

  delete ph;

  delete b;


  return 0;
}
