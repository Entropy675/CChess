#include "KingMove.h"

KingMove::KingMove(Piece* p) : MoveBehaviour(p) {}
KingMove::~KingMove() {}

void KingMove::checkPosition(int x, int y, std::vector<Pos>& out)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
	
	if(!Pos::isValid(x,y))
		return;
	if(temp != nullptr)
		if(temp->isWhite() == from->isWhite())
			return;
	
	Bitboard illegalMap;
	if(from->isWhite())
		illegalMap = from->getBoard()->getBlackAttackMap();
	else
		illegalMap = from->getBoard()->getWhiteAttackMap();
	
	if(!illegalMap[Pos(x,y)])
		out.push_back(Pos(x,y));
}

void KingMove::checkPosition(int x, int y, Bitboard& bb) const
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
	
	if(!Pos::isValid(x,y))
		return;
	if(temp != nullptr)
		if(temp->isWhite() == from->isWhite())
			return;
	
	Bitboard illegalMap;
	if(from->isWhite())
		illegalMap = from->getBoard()->getBlackAttackMap();
	else
		illegalMap = from->getBoard()->getWhiteAttackMap();
	
	
	if(!illegalMap[Pos(x,y)])
		bb.setBit(Pos(x,y));
}

void KingMove::validMoves(std::vector<Pos>& out)
{	
	Bitboard attackMap;

	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(from->getPos().getX() + dirs[x], from->getPos().getY() + dirs[y], out);
}

Bitboard KingMove::validMoves(Pos* p) const
{
	Bitboard bb;
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;

	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(searchFrom.getX() + dirs[x], searchFrom.getY() + dirs[y], bb);
	
	return bb;
}

// by ensuring that each piece can capture their surrounding squares, two kings can never get next to each other
Bitboard KingMove::validCaptures(Pos* p) const
{
	Bitboard bb;
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(searchFrom.getX() + dirs[x], searchFrom.getY() + dirs[y], bb);
	
	return bb;
}
