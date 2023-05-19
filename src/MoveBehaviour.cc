#include "MoveBehaviour.h"

MoveBehaviour::MoveBehaviour() {}
MoveBehaviour::~MoveBehaviour() {}

Bitboard MoveBehaviour::validCaptures(Piece* from)
{
	return validMoves(from);
}

bool MoveBehaviour::isValidMove(const Pos& to, Piece* from)
{
    return validMoves(from)[to];
}