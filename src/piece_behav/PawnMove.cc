#include "PawnMove.h"
#include "../Log.h"

PawnMove::PawnMove() : turnToEP(-1), capturableViaEP(nullptr) {}

PawnMove::~PawnMove()
{
	capturableViaEP = nullptr;
}

// this will probably happen in a branch on the condition of hasPawnBehaviour() not null when trying to move a piece.
// before trying to move to a position, use this check on that position 
// if this returns true, then that means that you just performed an enPassant.
// When this returns true, it kills the enPassantTarget. It is then the move funcs
// responsibility to move this pawn to the position and update values (like has moved etc) as per normal.
bool PawnMove::enPassantCheckAct(const Pos p, const Piece& target)
{
	Log a(1);

	// attempting to avoid case in which EnPassant is only required for the first turn after it is available
	if(capturableViaEP != nullptr && turnToEP != target.getBoard()->getMoves())
	{
		a.append(" ==ENPASSANT== ---*^\\> MOVE INVALID: " + std::to_string(turnToEP) + " vs " + std::to_string(target.getBoard()->getMoves()));

		capturableViaEP = nullptr;
		turnToEP = -1;
		a.flush();
	}
	
	a.append("---> Entering EP check.\n");
	a.setLogLevel(3);
	if(capturableViaEP != nullptr)
	{
		a.append("capturableViaEP: " + capturableViaEP->getPos().toString()+ "\n");
		a.setLogLevel(1);
		
		if(p.getY() == capturableViaEP->getPos().getY() + (target.isWhite() ? -1 : 1) && p.getX() == capturableViaEP->getPos().getX())
		{
			a.append(" ==ENPASSANT== ---*^\\> MATCH: " + p.toString() + "\n");
			capturableViaEP->die(); 
			capturableViaEP = nullptr;
			return true;
		}
		a.append("fail" + std::to_string(capturableViaEP->getPos().getY()));
	}

	a.append("---> Exiting EP check.\n");
	return false;
}

const Piece& PawnMove::getEnPassantTarget() const
{
	return *capturableViaEP;
}
	
void PawnMove::EPSetTarget(Piece* p, int tep)
{
	capturableViaEP = p;
	turnToEP = tep;
	p->epActivate();
}

// helper function used when calculating valid moves, sets the enPassantTarget when its valid for it to be set.
void PawnMove::EPValidateTarget(Piece* from, bool right)
{
	int dircheck = from->isWhite() ? -1 : 1;
	int leftOrRight = right ? 1 : -1;
	if(from->getBoard()->getPiece(Pos(from->getPos().getX() + leftOrRight, from->getPos().getY() + dircheck*2)) != nullptr)
	{
		PawnMove* pm = from->getBoard()->getPiece(Pos(from->getPos().getX() + leftOrRight, from->getPos().getY() + dircheck*2))->getPawnBehaviour();
		if (pm != nullptr && from->getBoard()->getPiece(Pos(from->getPos().getX() + leftOrRight, from->getPos().getY() + dircheck*2))->isWhite() != from->isWhite())
			pm->EPSetTarget(from, from->getBoard()->getMoves() + 1);
	}
}


// not gonna lie, this is slightly sus unreadable code, TODO: refactor when you have time using new Pos overloaded ops, make more readable
void PawnMove::validMoves(std::vector<Pos>& p, Piece* from)
{
	Log log(2); // requires >=2 global log level, disables local logs <2
	int dircheck = from->isWhite() ? -1 : 1;

	// forward moves
	if(from->getBoard()->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck)) == nullptr)
	{
		p.push_back(Pos(from->getPos().getX(), from->getPos().getY() + dircheck));
		
		// double move if first move, sets EP logic.
		if(!from->hasMoved() && from->getBoard()->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2)) == nullptr)
		{
			p.push_back(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2));

			// the following two check if either of the pieces next to this pawn is a pawn, then sets their enPassantTarget to this guy.
			EPValidateTarget(from, true);
			EPValidateTarget(from, false);
		}
	}


	// piece capture (diagonal)
	if(from->getBoard()->getPiece(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck)) != nullptr)
		p.push_back(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck));

	if(from->getBoard()->getPiece(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck)) != nullptr)
		p.push_back(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck));


	// logging, all possible moves are logged at level 2
	log.append("PAWN VALID MOVE: VArr " + std::to_string(p.size()) + ":");
	for (auto &x : p)
		log.append(x.toString() + ", ");
	log.setLogLevel(1);
	log.append(" trn: " + std::to_string(from->getBoard()->getTurnFEN()) + "total moves: " + std::to_string(from->getBoard()->getMoves()) + "\n");
}

bool PawnMove::isValidMove(const Pos& to, Piece* from)
{
	std::vector<Pos> templist;
	validMoves(templist, from);
	for(long unsigned int i = 0; i < templist.size(); i++)
		if(templist[i] == to)
			return true;
	return false;
}
