#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Bishop.h"
#include <vector>

Bishop::Bishop(Pos p, bool white)
{
	wchar_t pwide;
	chr.chars[0] = L'A';
	if(white)
		pwide = L'♝';
	else
		pwide = L'♗';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

Bishop::~Bishop()
{

}

bool Bishop::isValidMove(Pos p)
{
	
	return false;
}

void Bishop::validMoves(std::vector<Pos>* p, Piece* gameBoard) 
{
	

}

