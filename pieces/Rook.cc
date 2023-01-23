#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Rook.h"
#include <vector>

Rook::Rook(Pos p, bool white)
{
	wchar_t pwide;
	if(white)
		pwide = L'♜';
	else
		pwide = L'♖';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

bool Rook::isValidMove(Pos p)
{
	
	return false;
}

void Rook::validMoves(std::vector<Pos>* p, Piece* gameBoard) 
{
	

}

void Rook::move(Pos p) 
{


}
