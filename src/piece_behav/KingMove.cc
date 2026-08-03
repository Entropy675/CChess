#include "KingMove.h"

KingMove::KingMove(Piece* p) : MoveBehaviour(p) {}
KingMove::~KingMove() {}

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
	// The king controls every adjacent square, occupied or not, and regardless of
	// whether the opponent also attacks it. This is the raw control set (attack map),
	// distinct from validMoves which additionally excludes friendly and attacked squares.
	// Keeping it independent of any attack map also breaks the king<->king map cycle.
	Bitboard bb;
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	int dirs[] = {1, 0, -1};
	int size = sizeof(dirs)/sizeof(int);
	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
		{
			if(dirs[x] == 0 && dirs[y] == 0)
				continue; // the king's own square
			int nx = searchFrom.getX() + dirs[x];
			int ny = searchFrom.getY() + dirs[y];
			if(Pos::isValid(nx, ny))
				bb.setBit(Pos(nx, ny));
		}
	
	return bb;
}
