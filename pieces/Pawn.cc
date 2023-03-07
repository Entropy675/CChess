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
	NcLog a(3); // requires 2 global log level
	
	//int dircheck = white ? -1 : 1;
	// attempting to avoid case in which EnPassant is only required for the first turn after it is available
	if(capturableViaEP != nullptr && turnToEP != game->getTurn())
	{
		a.append("---> ENPASSANT MOVE INVALID", 1);
	
		capturableViaEP = nullptr;
		turnToEP = -1;
	}
	
	a.append("---> MOVING PWN\n", 1);
	if(capturableViaEP != nullptr)
	{
		a.append("---> PASSQ1 " + std::to_string(p.getX()) + " "  + std::to_string(p.getY()), 3);
		a.append("PIECEMOV: " + std::to_string(capturableViaEP->getPos().getX()) 
				+ " " + std::to_string(capturableViaEP->getPos().getY()) + "\n", 3);
				
		if(p.getY() == capturableViaEP->getPos().getY() - 1 || p.getY() == capturableViaEP->getPos().getY() + 1)
			a.append("pass" + std::to_string(capturableViaEP->getPos().getY()), 3);
		else
			a.append("fail" + std::to_string(capturableViaEP->getPos().getY()), 3);
		
		if((p.getY() == capturableViaEP->getPos().getY() - 1 || p.getY() == capturableViaEP->getPos().getY() + 1) && p.getX() == capturableViaEP->getPos().getX())
		{
			capturableViaEP->die();
			game->clearPiece(capturableViaEP->getPos()); // clear the piece ptr off the game board
			
			a.append(" ==ENP== ---*^\\> MATCH: " + std::to_string(p.getX()) + ", " + std::to_string(p.getY()) + "\n", 1);
			
			if(!hasMoved)
				hasMoved = true;
				
			pos = p;
			
			return true;
		}
	}
	
	return Piece::move(p);
}

void Pawn::validMoves(std::vector<Pos>& p)
{
	NcLog a(2); // requires >=2 global log level, disables local logs <2

	int dircheck = white ? -1 : 1;
	
	// forward moves (2 and 1 squares) as well as EnPassant logic
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
	
	// if piece is capturable (diagonal)
	if(game->getPiece(Pos(pos.getX() - dircheck, pos.getY() + dircheck)) != nullptr)
		p.push_back(Pos(pos.getX() - dircheck, pos.getY() + dircheck));
	
	if(game->getPiece(Pos(pos.getX() + dircheck, pos.getY() + dircheck)) != nullptr)
		p.push_back(Pos(pos.getX() + dircheck, pos.getY() + dircheck));
	
	if(capturableViaEP != nullptr)
		p.push_back(Pos(capturableViaEP->getPos().getX(), capturableViaEP->getPos().getY() + dircheck));
	
	
	
	
	
    a.append("VArr " + std::to_string(p.size()) + ":", 2);
    
    for (auto &x : p)
        a.append("[" + std::to_string(x.getX()) + "," + std::to_string(x.getY()) + "],", 2);
    
    a.append(" trn: " + std::to_string(game->getTurn()), 1);
}





