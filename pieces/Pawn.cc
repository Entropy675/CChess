#include "Pawn.h"

Pawn::Pawn(Pos p, bool white, Board* g) 
	: Piece(p, 'P', white, g), turnToEP(-1), capturableViaEP(nullptr) {}

Pawn::~Pawn() {}

bool Pawn::isValidMove(Pos p)
{
	return false;
}

void Pawn::enPassantTarget(Piece* p, int tep)
{
	capturableViaEP = p;
	turnToEP = tep;
}

bool Pawn::move(Pos p)
{
	
	NcLog a;
	
	Pos tmp = pos; // we need to account for the position reversal (the parent move changes piece position)
	
	a.add("Pre:  " + std::to_string(pos.getX()) + "," + std::to_string(pos.getY()) + "\n");
	bool vld = Piece::move(p); // vld reperesents a legal move
	a.add("Post: " + std::to_string(pos.getX()) + "," + std::to_string(pos.getY()) + "\n");
	
	if(!vld) // completely invalid move
		return false;
	
	
	int dircheck = white ? -1 : 1;
	// attempting to avoid case in which EnPassant is only required for the first turn after it is available
	if(capturableViaEP != nullptr)
	{
   		a.add("PASSED NULLCHK, GameTurn: " + std::to_string(game->getTurn()) + " Turn2Pass: " + std::to_string(turnToEP));
   		
   		if(turnToEP == game->getTurn())
   		{
   			a.add("TurnPass");
			if(Pos(p.getX(), p.getY() - dircheck) == capturableViaEP->getPos())
			{
	   			a.add("PASSED KILLCHK");
				capturableViaEP->die();
				game->clearPiece(Pos(p.getX(), p.getY() - dircheck));
				vld = true;
			}
   		}
   		else
   		{
   			a.add("---> ENPASSANT OVERRIDE, MOVE INVALID");
   			pos = tmp;
   			vld = false;
		}
		
		capturableViaEP = nullptr;
		turnToEP = -1;
	}
	
	return vld;
}

void Pawn::validMoves(std::vector<Pos>& p)
{
	NcLog a;

	int dircheck = white ? -1 : 1;
	
	if(game->getPiece(Pos(pos.getX(), pos.getY() + dircheck)) == nullptr)
	{
		p.push_back(Pos(pos.getX(), pos.getY() + dircheck));
		if(!hasMoved && game->getPiece(Pos(pos.getX(), pos.getY() + dircheck*2)) == nullptr)
		{
			p.push_back(Pos(pos.getX(), pos.getY() + dircheck*2));
			
			
			if(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck*2)) != nullptr)
				if (Pawn* pawn = dynamic_cast<Pawn*>(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck*2)))) 
					pawn->enPassantTarget(this, game->getTurn() + 1);
			
			if(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck*2)) != nullptr)
				if (Pawn* pawn = dynamic_cast<Pawn*>(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck*2)))) 
					pawn->enPassantTarget(this, game->getTurn() + 1);
		}
	}
	
	if(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck)) != nullptr)
		p.push_back(Pos(pos.getX() - dircheck, pos.getY() + dircheck));
	
	if(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck)) != nullptr)
		p.push_back(Pos(pos.getX() + dircheck, pos.getY() + dircheck));
	
	if(capturableViaEP != nullptr)
		p.push_back(Pos(capturableViaEP->getPos().getX(), capturableViaEP->getPos().getY() + dircheck));
	
    a.add("VArr " + std::to_string(p.size()) + ":");
    
    for (auto &x : p)
        a.add("[" + std::to_string(x.getX()) + "," + std::to_string(x.getY()) + "],");
    
    a.add(" trn: " + std::to_string(game->getTurn()));
}





