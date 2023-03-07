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

/*
bool Pawn::move(Pos p)
{
	
	NcLog a;
	
	Pos tmp = pos; // we need to account for the position reversal (the parent move changes piece position)
	
	a.append("Pre:  " + std::to_string(pos.getX()) + "," + std::to_string(pos.getY()) + "\n");
	bool vld = Piece::move(p); // vld reperesents a legal move
	a.append("Post: " + std::to_string(pos.getX()) + "," + std::to_string(pos.getY()) + "\n");
	
	if(!vld) // completely invalid move
		return false;
	
	
	int dircheck = white ? -1 : 1;
	// attempting to avoid case in which EnPassant is only required for the first turn after it is available
	if(capturableViaEP != nullptr)
	{
   		a.append("PASSED NULLCHK, GameTurn: " + std::to_string(game->getTurn()) + " Turn2Pass: " + std::to_string(turnToEP));
   		
   		if(turnToEP == game->getTurn())
   		{
   			a.append("TurnPass");
			if(Pos(p.getX(), p.getY() - dircheck) == capturableViaEP->getPos())
			{
	   			a.append("PASSED KILLCHK");
				capturableViaEP->die();
				game->clearPiece(Pos(p.getX(), p.getY() - dircheck));
				vld = true;
			}
   		}
   		else
   		{
   			a.append("---> ENPASSANT OVERRIDE, MOVE INVALID");
   			pos = tmp;
   			vld = false;
		}
		
		capturableViaEP = nullptr;
		turnToEP = -1;
	}
	
	return vld;
}
*/

bool Pawn::move(Pos p)
{
	NcLog a;
	
	//int dircheck = white ? -1 : 1;
	// attempting to avoid case in which EnPassant is only required for the first turn after it is available
	if(capturableViaEP != nullptr && turnToEP != game->getTurn())
	{
		a.append("---> ENPASSANT MOVE INVALID");
	
		capturableViaEP = nullptr;
		turnToEP = -1;
	}
	
	a.append("---> MOVING PWN\n");
	if(capturableViaEP != nullptr)
	{
		a.append("---> PASSQ1 " + std::to_string(p.getX()) + " "  + std::to_string(p.getY()));
		a.append("PIECEMOV: " + std::to_string(capturableViaEP->getPos().getX()) 
				+ " " + std::to_string(capturableViaEP->getPos().getY()) + "\n");
				
		if(p.getY() == capturableViaEP->getPos().getY() - 1 || p.getY() == capturableViaEP->getPos().getY() + 1)
			a.append("pass" + std::to_string(capturableViaEP->getPos().getY()));
		else
			a.append("fail" + std::to_string(capturableViaEP->getPos().getY()));
		
		if((p.getY() == capturableViaEP->getPos().getY() - 1 || p.getY() == capturableViaEP->getPos().getY() + 1) && p.getX() == capturableViaEP->getPos().getX())
		{
			capturableViaEP->die();
			game->clearPiece(capturableViaEP->getPos());
			
			a.append(" ==ENP== ---*^\\> MATCH: " + std::to_string(p.getX()) + ", " + std::to_string(p.getY()) + "\n");
			
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
	NcLog a;

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
	
	
	
	
	
    a.append("VArr " + std::to_string(p.size()) + ":");
    
    for (auto &x : p)
        a.append("[" + std::to_string(x.getX()) + "," + std::to_string(x.getY()) + "],");
    
    a.append(" trn: " + std::to_string(game->getTurn()));
}





