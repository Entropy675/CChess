#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include "Rook.h"
#include <vector>

Rook::Rook(Pos p, bool white, Board* g) : Piece(p, 'R', white, g)
{

}

Rook::~Rook()
{

}

bool Rook::isValidMove(const Pos p)
{

	return false;
}

void Rook::validMoves(std::vector<Pos>& p)
{

}
bool Rook::move(const Pos p)
{

	return false;
}
