#include "CrossMove.h"

CrossMove::CrossMove(Piece* p) : MoveBehaviour(p)  {}
CrossMove::~CrossMove() {}

// returns false meaning continue searching - have yet to hit a piece or invalid square.
Bitboard CrossMove::validMoves(Pos* p) const { return generate(p, false); }
Bitboard CrossMove::validCaptures(Pos* p) const { return generate(p, true); }

bool CrossMove::checkPosition(int x, int y, Bitboard& bb, bool attackMap) const
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x, y));
		if(temp == nullptr || temp == from) // if we are checking from a different position, we don't want to stop at the "ghost" of this piece, thus temp == from
			bb.setBit(Pos(x, y));
		else
		{
			if(temp->isWhite() != from->isWhite() || attackMap) // attack map includes defended friendly pieces
				bb.setBit(Pos(x, y));
			return true;
		}
		return false;
	}
	return true;			
}

Bitboard CrossMove::generate(Pos* p, bool attackMap) const
{
	Bitboard bb;
	if(from->isDead())
		return bb;
	
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	
	bool stopTR = false;
	bool stopTL = false;
	bool stopBR = false;
	bool stopBL = false;
	
	for(int i = 1; i < MAX_ROW_COL; i++)
	{
		if(!stopTL)
			stopTL = checkPosition(searchFrom.getX() - i, searchFrom.getY() - i, bb, attackMap);
		
		if(!stopTR)
			stopTR = checkPosition(searchFrom.getX() + i, searchFrom.getY() - i, bb, attackMap);
		
		if(!stopBR)
			stopBR = checkPosition(searchFrom.getX() + i, searchFrom.getY() + i, bb, attackMap);
		
		if(!stopBL)
			stopBL = checkPosition(searchFrom.getX() - i, searchFrom.getY() + i, bb, attackMap);
		
		if(stopTR && stopTL && stopBR && stopBL)
			break;
	}
	
	return bb;
}
	