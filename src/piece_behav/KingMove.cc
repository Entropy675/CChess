#include "KingMove.h"

KingMove::KingMove() {}
KingMove::~KingMove() {}

void KingMove::checkPosition(int x, int y, std::vector<Pos>& out, Bitboard& attackMap, Piece* from)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
	
	if(!Pos::isValid(x,y))
		return;
	if(temp != nullptr)
		if(temp->isWhite() == from->isWhite())
			return;
	
	if(!attackMap[Pos(x,y)])
		out.push_back(Pos(x,y));
}

void KingMove::checkPosition(int x, int y, Bitboard& bb, Bitboard& attackMap, Piece* from)
{
	Piece* temp = from->getBoard()->getPiece(Pos(x,y));
		
	if(!Pos::isValid(x,y))
		return;
	if(temp != nullptr)
		if(temp->isWhite() == from->isWhite())
			return;
	
	if(!attackMap[Pos(x,y)])
		bb.setBit(Pos(x,y));
}


void KingMove::validMoves(std::vector<Pos>& out, Piece* from)
{	
	Bitboard attackMap;
	if(from->isWhite())
		attackMap = from->getBoard()->getBlackAttackMap();
	else
		attackMap = from->getBoard()->getWhiteAttackMap();
	
	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(from->getPos().getX() + dirs[x], from->getPos().getY() + dirs[y], out, attackMap, from);
}

Bitboard KingMove::validMoves(Piece* from)
{
	Bitboard bb;
	
	Bitboard attackMap;
	if(from->isWhite())
		attackMap = from->getBoard()->getBlackAttackMap();
	else
		attackMap = from->getBoard()->getWhiteAttackMap();
	
	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			checkPosition(from->getPos().getX() + dirs[x], from->getPos().getY() + dirs[y], bb, attackMap, from);
	
	return bb;
}

bool KingMove::isValidMove(const Pos& to, Piece* from)
{
    return validMoves(from)[to];
}