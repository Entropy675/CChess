#include "MoveBehaviour.h"

MoveBehaviour::MoveBehaviour(Piece* p) : from(p) {}
MoveBehaviour::~MoveBehaviour() {}


Piece* MoveBehaviour::setFrom(Piece* p)
{
	Piece* r = from;
	from = p;
	return r;
}

Bitboard MoveBehaviour::validCaptures()
{
	return validMoves();
}

bool MoveBehaviour::isValidMove(const Pos& to)
{
    return validMoves()[to];
}