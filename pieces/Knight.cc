#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Knight.h"
#include <vector>

Knight::Knight(Pos p, bool white, Board* g) : Piece(p, 'N', white, g)
{
	
}

Knight::~Knight()
{

}

bool Knight::isValidMove(Pos p)
{
	
	return false;
}

void Knight::validMoves(std::vector<Pos>& p) 
{
	

}
