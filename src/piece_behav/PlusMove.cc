#include "PlusMove.h"

PlusMove::PlusMove() {}
PlusMove::~PlusMove() {}

// returns false meaning continue searching - have yet to hit a piece or invalid square.
bool PlusMove::checkPosition(int x, int y, std::vector<Pos>& out, Piece* from)
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

bool PlusMove::checkPosition(int x, int y, Bitboard& out, Piece* from)
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		if(temp == nullptr)
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


Bitboard PlusMove::validMoves(Piece* from)
{
	Bitboard bb;
	
	bool stopR = false;
	bool stopL = false;
	bool stopU = false;
	bool stopD = false;
	
	for(int i = 1; i < MAX_ROW_COL; i++)
	{
		if(!stopR)
			stopR = checkPosition(from->getPos().getX() + i, from->getPos().getY(), bb, from);
		
		if(!stopL)
			stopL = checkPosition(from->getPos().getX() - i, from->getPos().getY(), bb, from);
		
		if(!stopD)
			stopD = checkPosition(from->getPos().getX(), from->getPos().getY() + i, bb, from);
		
		if(!stopU)
			stopU = checkPosition(from->getPos().getX(), from->getPos().getY() - i, bb, from);
		
		if(stopU && stopD && stopR && stopL)
			break;
	}
	
	return bb;
}


void PlusMove::validMoves(std::vector<Pos>& out, Piece* from)
{
	Log log(2);
	bool stopR = false;
	bool stopL = false;
	bool stopU = false;
	bool stopD = false;
	
	for(int i = 1; i < MAX_ROW_COL; i++)
	{
		if(!stopR)
			stopR = checkPosition(from->getPos().getX() + i, from->getPos().getY(), out, from);
		
		if(!stopL)
			stopL = checkPosition(from->getPos().getX() - i, from->getPos().getY(), out, from);
		
		if(!stopD)
			stopD = checkPosition(from->getPos().getX(), from->getPos().getY() + i, out, from);
		
		if(!stopU)
			stopU = checkPosition(from->getPos().getX(), from->getPos().getY() - i, out, from);
		
		if(stopU && stopD && stopR && stopL)
			break;
	}
}

bool PlusMove::isValidMove(const Pos& to, Piece* from)
{
    return validMoves(from)[to];
}