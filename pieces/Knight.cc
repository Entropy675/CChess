#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Knight.h"
#include <vector>

Knight::Knight(Pos p, bool white)
{
	wchar_t pwide;
	if(white)
		pwide = L'♞';
	else
		pwide = L'♘';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

Knight::~Knight()
{

}

bool Knight::isValidMove(Pos p)
{
	
	return false;
}

void Knight::validMoves(std::vector<Pos>* p, Piece* gameBoard) 
{
	

}
