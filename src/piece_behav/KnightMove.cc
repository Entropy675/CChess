#include "KnightMove.h"

KnightMove::KnightMove(Piece* p) : MoveBehaviour(p)  {}
KnightMove::~KnightMove() {}

// returns true meaning cPos was added to out.
void KnightMove::checkPosition(int x, int y, std::vector<Pos>& out)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		
	if(!Pos::isValid(x,y))
		return;
	
	if(temp == nullptr)
		out.push_back(Pos(x,y));
	else if(temp->isWhite() != from->isWhite())
		out.push_back(Pos(x,y));
}

void KnightMove::checkPosition(int x, int y, Bitboard& bb)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		
	if(!Pos::isValid(x,y))
		return;
	
	if(temp == nullptr)
		bb.setBit(Pos(x,y));
	else if(temp->isWhite() != from->isWhite())
		bb.setBit(Pos(x,y));
}

// dynamic approach, can use precomputed move tables for more speed in future, this is fine for now.
Bitboard KnightMove::validMoves()
{
	Bitboard bb;
	if(from->isDead())
		return bb;
	
	if(Pos::isValid(from->getPos().getX() + 2, from->getPos().getY()))
	{
		checkPosition(from->getPos().getX() + 2, from->getPos().getY() + 1, bb);
		checkPosition(from->getPos().getX() + 2, from->getPos().getY() - 1, bb);
	}
	
	if(Pos::isValid(from->getPos().getX() - 2, from->getPos().getY()))
	{
		checkPosition(from->getPos().getX() - 2, from->getPos().getY() + 1, bb);
		checkPosition(from->getPos().getX() - 2, from->getPos().getY() - 1, bb);
	}
	
	if(Pos::isValid(from->getPos().getX(), from->getPos().getY() + 2))
	{
		checkPosition(from->getPos().getX() + 1, from->getPos().getY() + 2, bb);
		checkPosition(from->getPos().getX() - 1, from->getPos().getY() + 2, bb);
	}
	
	if(Pos::isValid(from->getPos().getX(), from->getPos().getY() - 2))
	{
		checkPosition(from->getPos().getX() + 1, from->getPos().getY() - 2, bb);
		checkPosition(from->getPos().getX() - 1, from->getPos().getY() - 2, bb);
	}
	
	return bb;
}
	
void KnightMove::validMoves(std::vector<Pos>& out)
{
	if(from->isDead())
		return;

	if(Pos::isValid(from->getPos().getX() + 2, from->getPos().getY()))
	{
		checkPosition(from->getPos().getX() + 2, from->getPos().getY() + 1, out);
		checkPosition(from->getPos().getX() + 2, from->getPos().getY() - 1, out);
	}
	
	if(Pos::isValid(from->getPos().getX() - 2, from->getPos().getY()))
	{
		checkPosition(from->getPos().getX() - 2, from->getPos().getY() + 1, out);
		checkPosition(from->getPos().getX() - 2, from->getPos().getY() - 1, out);
	}
	
	if(Pos::isValid(from->getPos().getX(), from->getPos().getY() + 2))
	{
		checkPosition(from->getPos().getX() + 1, from->getPos().getY() + 2, out);
		checkPosition(from->getPos().getX() - 1, from->getPos().getY() + 2, out);
	}
	
	if(Pos::isValid(from->getPos().getX(), from->getPos().getY() - 2))
	{
		checkPosition(from->getPos().getX() + 1, from->getPos().getY() - 2, out);
		checkPosition(from->getPos().getX() - 1, from->getPos().getY() - 2, out);
	}
}
