#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Queen.h"
#include <vector>

Queen::Queen(Pos p, bool white, Board* g) : Piece(p, 'Q', white, g)
{
	
}

Queen::~Queen()
{

}

bool Queen::isValidMove(Pos p)
{
	
	return false;
}

void Queen::validMoves(std::vector<Pos>& p)
{
	

}
