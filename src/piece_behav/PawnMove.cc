#include "PawnMove.h"
#include "../Log.h"

PawnMove::PawnMove(Piece* p) : MoveBehaviour(p), turnToEP(-1), capturableViaEP(nullptr) {}

PawnMove::~PawnMove()
{
	capturableViaEP = nullptr;
}

// Before trying to move a pawn to a position, use this check on that position.
// When this returns true, it kills the enPassantTarget. 
// It is then the move funcs responsibility to move this pawn to the position and update values (like has moved etc) as per normal.
bool PawnMove::enPassantCheckAct(const Pos p, const Piece& target)
{
	Log a(3);

	// attempting to avoid case in which EnPassant is only required for the first turn after it is available
	if(capturableViaEP != nullptr && turnToEP != target.getBoard()->getMoves())
	{
		a.append(" ==ENPASSANT== ---*^\\> MOVE INVALID: " + std::to_string(turnToEP) + " vs " + std::to_string(target.getBoard()->getMoves()));

		capturableViaEP = nullptr;
		turnToEP = -1;
		a.flush();
	}
	
	if(capturableViaEP != nullptr)
	{
		if(p.getY() == capturableViaEP->getPos().getY() + (target.isWhite() ? -1 : 1) && p.getX() == capturableViaEP->getPos().getX())
		{
			a.append(" ==ENPASSANT== ---*^\\> MATCH: " + p.toString() + "\n");
			capturableViaEP->die(true); 
			capturableViaEP = nullptr;
			return true;
		}
		a.append("fail" + std::to_string(capturableViaEP->getPos().getY()));
	}
	return false;
}

const Piece* PawnMove::getEnPassantTarget() const
{
	return capturableViaEP;
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

Bitboard PawnMove::validCaptures(Pos* p) const
{
	Bitboard bb;
	if(from->isDead())
		return bb;
	
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	int dircheck = from->isWhite() ? -1 : 1;
	
	if(Pos::isValid(searchFrom.getX() - 1, searchFrom.getY() + dircheck))
		bb.setBit(Pos(searchFrom.getX() - 1, searchFrom.getY() + dircheck));
	
	if(Pos::isValid(searchFrom.getX() + 1, searchFrom.getY() + dircheck))
		bb.setBit(Pos(searchFrom.getX() + 1, searchFrom.getY() + dircheck));
	
	return bb;
}

Bitboard PawnMove::validMoves(Pos* p) const
{
	Bitboard bb;
	if(from->isDead())
		return bb;
	
	Pos searchFrom = (p == nullptr) ? from->getPos() : *p;
	
	int dircheck = from->isWhite() ? -1 : 1;
	Board* game = from->getBoard();

	// forward moves
	if(game->getPiece(Pos(searchFrom.getX(), searchFrom.getY() + dircheck)) == nullptr)
	{
		bb.setBit(Pos(searchFrom.getX(), searchFrom.getY() + dircheck));
		if(!from->hasMoved() && game->getPiece(Pos(searchFrom.getX(), searchFrom.getY() + dircheck*2)) == nullptr)
			bb.setBit(Pos(searchFrom.getX(), searchFrom.getY() + dircheck*2));
	}

	// piece capture (diagonal) -1 for left, 1 for right.
	if(game->getPiece(Pos(searchFrom.getX() - 1, searchFrom.getY() + dircheck)) != nullptr && Pos::isValid(searchFrom.getX() - 1, searchFrom.getY() + dircheck))
		bb.setBit(Pos(searchFrom.getX() - 1, searchFrom.getY() + dircheck));

	if(game->getPiece(Pos(searchFrom.getX() + 1, searchFrom.getY() + dircheck)) != nullptr && Pos::isValid(searchFrom.getX() + 1, searchFrom.getY() + dircheck))
		bb.setBit(Pos(searchFrom.getX() + 1, searchFrom.getY() + dircheck));
	
	return bb;
}

void PawnMove::validMoves(std::vector<Pos>& p)
{
	if(from->isDead())
		return;
	int dircheck = from->isWhite() ? -1 : 1;

	// forward moves
	if(from->getBoard()->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck)) == nullptr)
	{
		p.push_back(Pos(from->getPos().getX(), from->getPos().getY() + dircheck));
		
		if(!from->hasMoved() && from->getBoard()->getPiece(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2)) == nullptr)
			p.push_back(Pos(from->getPos().getX(), from->getPos().getY() + dircheck*2));
	}


	// piece capture (diagonal)
	if(from->getBoard()->getPiece(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck)) != nullptr)
		p.push_back(Pos(from->getPos().getX() - 1, from->getPos().getY() + dircheck));

	if(from->getBoard()->getPiece(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck)) != nullptr)
		p.push_back(Pos(from->getPos().getX() + 1, from->getPos().getY() + dircheck));
}
