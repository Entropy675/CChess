#include "KnightMove.h"

KnightMove::KnightMove(Piece* p) : MoveBehaviour(p)  {}
KnightMove::~KnightMove() {}

// returns true meaning cPos was added to out.
Bitboard KnightMove::validMoves(Pos* p) const { return generate(p, false); }
Bitboard KnightMove::validCaptures(Pos* p) const { return generate(p, true); }

void KnightMove::checkPosition(int x, int y, Bitboard& bb, bool attackMap) const
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		
	if(!Pos::isValid(x,y))
		return;
	
	if(temp == nullptr)
		bb.setBit(Pos(x,y));
	else if(temp->isWhite() != from->isWhite() || attackMap) // attack map includes defended friendly pieces
		bb.setBit(Pos(x,y));
}

// dynamic approach, can use precomputed move tables for more speed in future, this is fine for now.
Bitboard KnightMove::generate(Pos* p, bool attackMap) const
{
	Bitboard bb;
	if(from->isDead())
		return bb;
	
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	if(Pos::isValid(searchFrom.getX() + 2, searchFrom.getY()))
	{
		checkPosition(searchFrom.getX() + 2, searchFrom.getY() + 1, bb, attackMap);
		checkPosition(searchFrom.getX() + 2, searchFrom.getY() - 1, bb, attackMap);
	}
	
	if(Pos::isValid(searchFrom.getX() - 2, searchFrom.getY()))
	{
		checkPosition(searchFrom.getX() - 2, searchFrom.getY() + 1, bb, attackMap);
		checkPosition(searchFrom.getX() - 2, searchFrom.getY() - 1, bb, attackMap);
	}
	
	if(Pos::isValid(searchFrom.getX(), searchFrom.getY() + 2))
	{
		checkPosition(searchFrom.getX() + 1, searchFrom.getY() + 2, bb, attackMap);
		checkPosition(searchFrom.getX() - 1, searchFrom.getY() + 2, bb, attackMap);
	}
	
	if(Pos::isValid(searchFrom.getX(), searchFrom.getY() - 2))
	{
		checkPosition(searchFrom.getX() + 1, searchFrom.getY() - 2, bb, attackMap);
		checkPosition(searchFrom.getX() - 1, searchFrom.getY() - 2, bb, attackMap);
	}
	
	return bb;
}
	