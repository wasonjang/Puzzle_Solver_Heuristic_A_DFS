#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
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
      if(s  < _size){
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
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& input)
{
  _size = input.size();
  _tiles = new int[_size];
  for(int i=0; i<_size; i++)
  {
    _tiles[i] = input[i];
  }
}


Board::~Board()
{
  delete [] _tiles;
}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  int side_dim = dim();
  map<int, Board*>newboard;
  int blankrow;
  int blankcol;
  //find the blank row and column
  int i=-1;
  while(_tiles[++i] != 0);

  blankrow = i / side_dim;
  blankcol = i % side_dim;
  //check bound
  if(blankrow - 1 >= 0)
  {
    int possibletitle1;
    //get the tile above.
    possibletitle1 = _tiles[i - side_dim];
    //new board - copy constructor needed
    Board* b1 = new Board(*this);
    //move the configuration to match the possible move.
    b1->move(possibletitle1);
    //push into the map
    newboard.insert(make_pair(possibletitle1,b1));
  }
  //check bound
  if(blankrow + 1 < side_dim)
  {
    int possibletitle2;
    //get the tile below.
    possibletitle2 = _tiles[i + side_dim];
    Board* b2 = new Board(*this);
    b2->move(possibletitle2);
    newboard.insert(make_pair(possibletitle2,b2));
  }
  //check bound
  if(blankcol - 1 >= 0)
  {
    int possibletitle3;
    //get the left tile
    possibletitle3 = _tiles[i - 1];
    Board* b3 = new Board(*this);
    b3->move(possibletitle3);
    newboard.insert(make_pair(possibletitle3,b3));
  }
  //check bound
  if(blankcol + 1 < side_dim)
  {
    int possibletitle4;
    // get the right tile
    possibletitle4 = _tiles[i + 1];
    Board* b4 = new Board(*this);
    b4->move(possibletitle4);
    newboard.insert(make_pair(possibletitle4,b4));

  }
  
  return newboard;
}
bool Board::solved() const
{
  for(int i=0; i<_size; i++)
  {
    if(_tiles[i] != i)
    {
      return false;
    }
  }
  return true;
}

  // Checks if this board is less-than another.  We define less than
  // as a "string-style" comparison of the tile array (i.e. Starting by comparing
  // the 0-th tile in this Board and the other.
  // If this board's tile is less than the other board's tile value, return true
  // If they are equal, continue with the next tile location and repeat
bool Board::operator<(const Board& rhs) const
{
  //walkthrough each tile
  for(int i = 0; i<_size; i++)
  {
    //if less than rhs's return true
    if(_tiles[i] < rhs[i])
    {
      return true;
    }
    else if(_tiles[i] > rhs[i])
    {
      return false;
    }
    else if(_tiles[i] == rhs[i])
    {
      continue;
    }
  } 
  //return false if no less found
  return false;
}
std::ostream& operator<<(std::ostream &os, const Board &b)
{
  int side_dim = b.dim();
  for(int i = 0; i<side_dim; i++)
  {
    b.printRowBanner(os);
    for(int j = 0; j<side_dim; j++)
    {
      os<<"|";
      if(b[i*side_dim+j] == 0)
      {
        os<<"  ";
      }
      else if(b[i*side_dim+j] >= 10)
      {
        os<<b[i*side_dim+j];
      }
      else
      {
        os<<" "<<b[i*side_dim+j];
      }

    }
    os<<"|";
    os<<endl;
  }
  b.printRowBanner(os);

  return os;

}
const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
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
