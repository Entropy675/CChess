#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Pawn.h"
#include <vector>

#include <string>
#include <ncurses.h>

#include "../NcLog.h"

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

void Pawn::validMoves(std::vector<Pos>* p, Piece* (&gameBoard)[MAX_ROW_COL][MAX_ROW_COL])
{
	NcLog a;
	
	int dircheck = -1;
	if(!isWhite)
		dircheck = 1;
	
	a.logStr("[" + std::to_string(pos.getX()) + "," + std::to_string(pos.getY()) + "]"
	+ "\n  [" + std::to_string(pos.getX()) + "," + std::to_string(pos.getY() + dircheck) + "]"
	+ "\n  isnull: " + std::to_string(gameBoard[pos.getX()][pos.getY() + dircheck] == nullptr)
	);
	
	if(gameBoard[pos.getX()][pos.getY() + dircheck] == nullptr)
	{
		p->push_back(Pos(pos.getX(), pos.getY() + dircheck));
		
		if(!hasMoved && gameBoard[pos.getX()][pos.getY() + dircheck*2] == nullptr)
			p->push_back(Pos(pos.getX(), pos.getY() + dircheck*2));
	}
	
	
    std::string str = "VArr " + std::to_string((*p).size()) + ": ";
    
    for (auto &x : *p)
        str += "[" + std::to_string(x.getX()) + "," + std::to_string(x.getY()) + "], ";
    
    
    a.logStr(str);
}

