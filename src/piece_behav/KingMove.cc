#include "KingMove.h"

KingMove::KingMove() {}
KingMove::~KingMove() {}

void KingMove::validMoves(std::vector<Pos>& out, Piece* from)
{
	//if(!Pos::isValid(x,y))
		//return;
	
}

Bitboard KingMove::validMoves(Piece* from)
{
	Bitboard bb;
	
	
	
	return bb;
}

bool KingMove::isValidMove(const Pos& to, Piece* from)
{
	
	// probably not this simple haha
    return validMoves(from)[to];
}