#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Pawn.h"
#include <vector>

#include <string>
#include <ncurses.h>

#include "../NcLog.h"

Pawn::Pawn(Pos p, bool white, Board* g) 
	: Piece(p, 'P', white, g), canEP(false), capturableViaEP(nullptr)
{
	
}

Pawn::~Pawn()
{
	
}

bool Pawn::isValidMove(Pos p)
{
	
	return false;
}

void Pawn::enPassantTarget(Piece* p)
{
	capturableViaEP = p;
}

bool Pawn::move(Pos pos)
{
	bool vld = Piece::move(pos);
	
	NcLog a;
	
	int dircheck = -1;
	if(!white)
		dircheck = 1;
		
	if(vld && capturableViaEP != nullptr)
	{
   		a.add("PASSED NULLCHK");
		if(Pos(pos.getX(), pos.getY() - dircheck) == capturableViaEP->getPos())
		{
   			a.add("PASSED KILLCHK");
			capturableViaEP->die();
			game->clearPiece(Pos(pos.getX(), pos.getY() - dircheck));
		}
	}
	
	return vld;
}

void Pawn::validMoves(std::vector<Pos>& p)
{
	NcLog a;
	
	int dircheck = -1;
	
	if(!white)
		dircheck = 1;
	

	
	if(game->getPiece(Pos(pos.getX(), pos.getY() + dircheck)) == nullptr)
	{
		p.push_back(Pos(pos.getX(), pos.getY() + dircheck));
		if(!hasMoved && game->getPiece(Pos(pos.getX(), pos.getY() + dircheck*2)) == nullptr)
		{
			p.push_back(Pos(pos.getX(), pos.getY() + dircheck*2));
			
			
			if(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck*2)) != nullptr)
				if (Pawn* pawn = dynamic_cast<Pawn*>(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck*2)))) 
					pawn->enPassantTarget(this);
			
			if(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck*2)) != nullptr)
				if (Pawn* pawn = dynamic_cast<Pawn*>(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck*2)))) 
					pawn->enPassantTarget(this);
		}
	}
	
	if(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck)) != nullptr)
		p.push_back(Pos(pos.getX() - dircheck, pos.getY() + dircheck));
	
	if(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck)) != nullptr)
		p.push_back(Pos(pos.getX() + dircheck, pos.getY() + dircheck));
	
	if(capturableViaEP != nullptr)
	{
		if(game->getPiece(Pos(pos.getX() + dircheck, pos.getY())) == capturableViaEP)
		{
			clearEnPassantPiece[0] = this;
			p.push_back(Pos(pos.getX() + dircheck, pos.getY() + dircheck));
		}
		
		if(game->getPiece(Pos(pos.getX() - dircheck, pos.getY())) == capturableViaEP)
		{
			clearEnPassantPiece[1] = this;
			p.push_back(Pos(pos.getX() - dircheck, pos.getY() + dircheck));
		}
		
	}
	
    a.add("VArr " + std::to_string(p.size()) + ":");
    
    for (auto &x : p)
        a.add("[" + std::to_string(x.getX()) + "," + std::to_string(x.getY()) + "],");
    
}





