#include "CrossMove.h"

CrossMove::CrossMove(Piece* p) : MoveBehaviour(p)  {}
CrossMove::~CrossMove() {}

// returns false meaning continue searching - have yet to hit a piece or invalid square.
bool CrossMove::checkPosition(int x, int y, std::vector<Pos>& out)
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x, y));
		if(temp == nullptr)
			out.push_back(Pos(x, y));
		else
		{
			if(temp->isWhite() != from->isWhite())
				out.push_back(Pos(x, y));
			return true;
		}
		return false;
	}
	return true;			
}

bool CrossMove::checkPosition(int x, int y, Bitboard& bb) const
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x, y));
		if(temp == nullptr || temp == from) // if we are checking from a different position, we don't want to stop at the "ghost" of this piece, thus temp == from
			bb.setBit(Pos(x, y));
		else
		{
			if(temp->isWhite() != from->isWhite())
				bb.setBit(Pos(x, y));
			return true;
		}
		return false;
	}
	return true;			
}

Bitboard CrossMove::validMoves(Pos* p) const
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
			stopTL = checkPosition(searchFrom.getX() - i, searchFrom.getY() - i, bb);
		
		if(!stopTR)
			stopTR = checkPosition(searchFrom.getX() + i, searchFrom.getY() - i, bb);
		
		if(!stopBR)
			stopBR = checkPosition(searchFrom.getX() + i, searchFrom.getY() + i, bb);
		
		if(!stopBL)
			stopBL = checkPosition(searchFrom.getX() - i, searchFrom.getY() + i, bb);
		
		if(stopTR && stopTL && stopBR && stopBL)
			break;
	}
	
	return bb;
}
	
void CrossMove::validMoves(std::vector<Pos>& out)
{
	if(from->isDead())
		return;
	
	bool stopTR = false;
	bool stopTL = false;
	bool stopBR = false;
	bool stopBL = false;
	
	for(int i = 1; i < MAX_ROW_COL; i++)
	{
		if(!stopTL)
			stopTL = checkPosition(from->getPos().getX() - i, from->getPos().getY() - i, out);
		
		if(!stopTR)
			stopTR = checkPosition(from->getPos().getX() + i, from->getPos().getY() - i, out);
		
		if(!stopBR)
			stopBR = checkPosition(from->getPos().getX() + i, from->getPos().getY() + i, out);
		
		if(!stopBL)
			stopBL = checkPosition(from->getPos().getX() - i, from->getPos().getY() + i, out);
		
		if(stopTR && stopTL && stopBR && stopBL)
			break;
	}
}
