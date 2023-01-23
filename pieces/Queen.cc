#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Queen.h"
#include <vector>

Queen::Queen(Pos p, bool white)
{
	wchar_t pwide;
	if(white)
		pwide = L'♛';
	else
		pwide = L'♕';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

bool Queen::isValidMove(Pos p)
{
	
	return false;
}

void Queen::validMoves(std::vector<Pos>* p, Piece* gameBoard) 
{
	

}

void Queen::move(Pos p) 
{


}
