#include "PlusMove.h"

PlusMove::PlusMove(Piece* from) : MoveBehaviour(from) {}
PlusMove::~PlusMove() {}

// returns false meaning continue searching - have yet to hit a piece or invalid square.
bool PlusMove::checkPosition(int x, int y, std::vector<Pos>& out)
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		if(temp == nullptr)
			out.push_back(Pos(x,y));
		else
		{
			if(temp->isWhite() != from->isWhite())
				out.push_back(Pos(x,y));
			return true;
		}
		return false;
	}
	return true;
}

bool PlusMove::checkPosition(int x, int y, Bitboard& out) const
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		if(temp == nullptr || temp == from)
			out.setBit(Pos(x,y));
		else
		{
			if(temp->isWhite() != from->isWhite())
				out.setBit(Pos(x,y));
			return true;
		}
		return false;
	}
	return true;
}


Bitboard PlusMove::validMoves(Pos* p) const
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
			stopR = checkPosition(searchFrom.getX() + i, searchFrom.getY(), bb);
		
		if(!stopL)
			stopL = checkPosition(searchFrom.getX() - i, searchFrom.getY(), bb);
		
		if(!stopD)
			stopD = checkPosition(searchFrom.getX(), searchFrom.getY() + i, bb);
		
		if(!stopU)
			stopU = checkPosition(searchFrom.getX(), searchFrom.getY() - i, bb);
		
		if(stopU && stopD && stopR && stopL)
			break;
	}
	
	return bb;
}


void PlusMove::validMoves(std::vector<Pos>& out)
{
	if(from->isDead())
		return;
	
	Log log(2);
	bool stopR = false;
	bool stopL = false;
	bool stopU = false;
	bool stopD = false;
	
	for(int i = 1; i < MAX_ROW_COL; i++)
	{
		if(!stopR)
			stopR = checkPosition(from->getPos().getX() + i, from->getPos().getY(), out);
		
		if(!stopL)
			stopL = checkPosition(from->getPos().getX() - i, from->getPos().getY(), out);
		
		if(!stopD)
			stopD = checkPosition(from->getPos().getX(), from->getPos().getY() + i, out);
		
		if(!stopU)
			stopU = checkPosition(from->getPos().getX(), from->getPos().getY() - i, out);
		
		if(stopU && stopD && stopR && stopL)
			break;
	}
}
