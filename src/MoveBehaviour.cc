#include "MoveBehaviour.h"

MoveBehaviour::MoveBehaviour(Piece* p) : from(p) {}
MoveBehaviour::~MoveBehaviour() {}


Piece* MoveBehaviour::setFrom(Piece* p)
{
	Piece* r = from;
	from = p;
	return r;
}

Bitboard MoveBehaviour::validCaptures(Pos* p) const
{
	return (p == nullptr) ? validMoves() : validMoves(p);
}

bool MoveBehaviour::isValidMove(const Pos& to)
{
    return validMoves()[to];
}