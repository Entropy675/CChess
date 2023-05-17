#include "PawnMove.h"
#include "../Log.h"

PawnMove::PawnMove() : turnToEP(-1), capturableViaEP(nullptr) {}

PawnMove::~PawnMove()
{
	capturableViaEP = nullptr;
}

// Before trying to move a pawn to a position, use this check on that position.
// When this returns true, it kills the enPassantTarget. 
// It is then the move funcs responsibility to move this pawn to the position and update values (like has moved etc) as per normal.
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
	if (capturableViaEP == nullptr) 
		throw std::logic_error("Fatal error: En passant target is nullptr when getting target. Something is wrong with control flow, this mustn't be called before appropriate checks are made.");
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
	Board* game = from->getBoard();
	Piece* target = game->getPiece(Pos(from->getPos().getX() + (right ? 1 : -1), from->getPos().getY() + (from->isWhite() ? -1 : 1)*2));
	if(target != nullptr)
	{
		PawnMove* pm = target->getPawnBehaviour();
		if (pm != nullptr && target->isWhite() != from->isWhite())
			pm->EPSetTarget(from, game->getMoves() + 1);
	}
}

Bitboard PawnMove::validMoves(Piece* from)
{
	Bitboard bb;
	int dircheck = from->isWhite() ? -1 : 1;
	Board* game = from->getBoard();

	// forward moves
	if(game->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck)) == nullptr)
	{
		bb.setBit(Pos(from->getPos().getX(), from->getPos().getY() + dircheck));
		
		if(!from->hasMoved() && game->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2)) == nullptr)
		{
			bb.setBit(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2));

			// the following two check if either of the pieces next to this pawn is a pawn, then sets their enPassantTarget to this one.
			EPValidateTarget(from, true);
			EPValidateTarget(from, false);
		}
	}


	// piece capture (diagonal) -1 for left, 1 for right.
	if(game->getPiece(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck)) != nullptr)
		bb.setBit(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck));

	if(game->getPiece(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck)) != nullptr)
		bb.setBit(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck));
	
	return bb;
}

// TODO: refactor to something cleaner when you have time
void PawnMove::validMoves(std::vector<Pos>& p, Piece* from)
{
	int dircheck = from->isWhite() ? -1 : 1;

	// forward moves
	if(from->getBoard()->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck)) == nullptr)
	{
		p.push_back(Pos(from->getPos().getX(), from->getPos().getY() + dircheck));
		
		if(!from->hasMoved() && from->getBoard()->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2)) == nullptr)
		{
			p.push_back(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2));

			// the following two check if either of the pieces next to this pawn is a pawn, then sets their enPassantTarget to this one.
			EPValidateTarget(from, true);
			EPValidateTarget(from, false);
		}
	}


	// piece capture (diagonal)
	if(from->getBoard()->getPiece(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck)) != nullptr)
		p.push_back(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck));

	if(from->getBoard()->getPiece(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck)) != nullptr)
		p.push_back(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck));
}

bool PawnMove::isValidMove(const Pos& to, Piece* from)
{
    return validMoves(from)[to];
}
