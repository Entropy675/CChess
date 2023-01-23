#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "King.h"
#include <vector>

King::King(Pos p, bool white)
{
	wchar_t pwide;
	if(white)
		pwide = L'♚';
	else
		pwide = L'♔';
	
	setcchar(&chr, &pwide, A_NORMAL, 0, NULL);
	pos.setX(p.getX());
	pos.setY(p.getY());
}

King::~King()
{

}

bool King::isValidMove(Pos p)
{
	
	return false;
}

void King::validMoves(std::vector<Pos>* p, Piece* gameBoard) 
{
	

}

void King::move(Pos p) 
{


}
