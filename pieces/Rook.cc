#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Rook.h"
#include <vector>

Rook::Rook(Pos p, bool white)
{
	wchar_t pwide;
	chr.chars[0] = L'A';
	if(white)
		pwide = L'♜';
	else
		pwide = L'♖';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

Rook::~Rook()
{

}

bool Rook::isValidMove(Pos p)
{
	
	return false;
}

void Rook::validMoves(std::vector<Pos>* p, Piece* (&gameBoard)[MAX_ROW_COL][MAX_ROW_COL])
{
	

}

