#include "KingMove.h"

KingMove::KingMove() {}
KingMove::~KingMove() {}

void KingMove::checkPosition(int x, int y, std::vector<Pos>& out, Piece* from)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
	
	if(!Pos::isValid(x,y))
		return;
	if(temp != nullptr)
		if(temp->isWhite() == from->isWhite())
			return;
	
	Bitboard attackMap;
	if(from->isWhite())
		attackMap = from->getBoard()->getBlackAttackMap();
	else
		attackMap = from->getBoard()->getWhiteAttackMap();
	
	if(!attackMap[Pos(x,y)])
		out.push_back(Pos(x,y));
}

void KingMove::checkPosition(int x, int y, Bitboard& bb, Piece* from, bool checkAtkMap)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
	
	if(!Pos::isValid(x,y))
		return;
	if(temp != nullptr)
		if(temp->isWhite() == from->isWhite())
			return;
		
	Bitboard attackMap;
	if(checkAtkMap)
	{
		if(from->isWhite())
			attackMap = from->getBoard()->getBlackAttackMap();
		else
			attackMap = from->getBoard()->getWhiteAttackMap();
	}
	
	if(!attackMap[Pos(x,y)])
		bb.setBit(Pos(x,y));
}

void KingMove::validMoves(std::vector<Pos>& out, Piece* from)
{	
	Bitboard attackMap;

	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(from->getPos().getX() + dirs[x], from->getPos().getY() + dirs[y], out, from);
}

Bitboard KingMove::validMoves(Piece* from)
{
	Bitboard bb;

	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(from->getPos().getX() + dirs[x], from->getPos().getY() + dirs[y], bb, from);
	
	return bb;
}

// by ensuring that each piece can capture their surrounding squares, two kings can never get next to each other
Bitboard KingMove::validCaptures(Piece* from)
{
	Bitboard bb;
	
	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(from->getPos().getX() + dirs[x], from->getPos().getY() + dirs[y], bb, from, false);
	
	return bb;
}
