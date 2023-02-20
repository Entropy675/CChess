#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "King.h"
#include <vector>

King::King(Pos p, bool white, Board* g) : Piece(p, 'K', white, g)
{
	
}

King::~King()
{

}

bool King::isValidMove(Pos p)
{
	
	return false;
}

void King::validMoves(std::vector<Pos>& p)
{
	

}

