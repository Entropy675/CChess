#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Pawn.h"
#include <vector>

Pawn::Pawn(Pos p, bool white)
{
	wchar_t pwide;
	if(white)
		pwide = L'♟';
	else
		pwide = L'♙';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

Pawn::~Pawn()
{
	
}

bool Pawn::isValidMove(Pos p)
{
	
	return false;
}

void Pawn::validMoves(std::vector<Pos>* p, Piece* gameBoard) 
{
	

}

void Pawn::move(Pos p) 
{


}
