#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Pawn.h"
#include <vector>

#include <string>
#include <ncurses.h>

#include "../NcLog.h"

Pawn::Pawn(Pos p, bool white, Board* g) : Piece(p, 'P', white, g)
{
	
}

Pawn::~Pawn()
{
	
}

bool Pawn::isValidMove(Pos p)
{
	
	return false;
}

void Pawn::validMoves(std::vector<Pos>& p)
{
	NcLog a;
	
	int dircheck = -1;
	if(!white)
		dircheck = 1;
	
	a.logStr("[" + std::to_string(pos.getX()) + "," + std::to_string(pos.getY()) + "]"
	+ "\n  [" + std::to_string(pos.getX()) + "," + std::to_string(pos.getY() + dircheck) + "]"
	+ "\n  isnull: " + std::to_string(game->getPiece(Pos(pos.getX(), pos.getY() + dircheck)) == nullptr)
	);
	
	if(game->getPiece(Pos(pos.getX(), pos.getY() + dircheck)) == nullptr)
	{
		p.push_back(Pos(pos.getX(), pos.getY() + dircheck));
		
		if(!hasMoved && game->getPiece(Pos(pos.getX(), pos.getY() + dircheck*2)) == nullptr)
			p.push_back(Pos(pos.getX(), pos.getY() + dircheck*2));
	}
	
	
    std::string str = "VArr " + std::to_string(p.size()) + ": ";
    
    for (auto &x : p)
        str += "[" + std::to_string(x.getX()) + "," + std::to_string(x.getY()) + "], ";
    
    
    a.logStr(str);
}

