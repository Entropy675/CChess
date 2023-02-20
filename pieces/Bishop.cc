#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Bishop.h"
#include <vector>

Bishop::Bishop(Pos p, bool white, Board* g) : Piece(p, 'B', white, g)
{
	
}

Bishop::~Bishop()
{

}

bool Bishop::isValidMove(Pos p)
{
	
	return false;
}

void Bishop::validMoves(std::vector<Pos>& p)
{
	

}

