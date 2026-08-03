#include "PlusMove.h"

PlusMove::PlusMove(Piece* from) : MoveBehaviour(from) {}
PlusMove::~PlusMove() {}

// returns false meaning continue searching - have yet to hit a piece or invalid square.
Bitboard PlusMove::validMoves(Pos* p) const { return generate(p, false); }
Bitboard PlusMove::validCaptures(Pos* p) const { return generate(p, true); }

bool PlusMove::checkPosition(int x, int y, Bitboard& out, bool attackMap) const
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		if(temp == nullptr || temp == from)
			out.setBit(Pos(x,y));
		else
		{
			if(temp->isWhite() != from->isWhite() || attackMap) // attack map includes defended friendly pieces
				out.setBit(Pos(x,y));
			return true;
		}
		return false;
	}
	return true;
}


Bitboard PlusMove::generate(Pos* p, bool attackMap) const
{
	Bitboard bb;
	if(from->isDead())
		return bb;
	
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	bool stopR = false;
	bool stopL = false;
	bool stopU = false;
	bool stopD = false;
	
	for(int i = 1; i < MAX_ROW_COL; i++)
	{
		if(!stopR)
			stopR = checkPosition(searchFrom.getX() + i, searchFrom.getY(), bb, attackMap);
		
		if(!stopL)
			stopL = checkPosition(searchFrom.getX() - i, searchFrom.getY(), bb, attackMap);
		
		if(!stopD)
			stopD = checkPosition(searchFrom.getX(), searchFrom.getY() + i, bb, attackMap);
		
		if(!stopU)
			stopU = checkPosition(searchFrom.getX(), searchFrom.getY() - i, bb, attackMap);
		
		if(stopU && stopD && stopR && stopL)
			break;
	}
	
	return bb;
}

