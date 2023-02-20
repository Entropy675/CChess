#include "Piece.h"

#include "NcLog.h"

Piece::Piece(Pos p, char c, bool w, Board* g) : pos(p), hasMoved(false), dead(false), chr(c), white(w), game(g) {}
Piece::~Piece() {}

bool Piece::move(Pos cPos)
{
	std::vector<Pos> p;
	validMoves(p);
	
	NcLog a;
	
	bool isValid = false;
	
	for(std::vector<Pos>::size_type i = 0; i < p.size(); i++)
		if(p.at(i) == cPos)
			isValid = true;
			
	a.logStr("Valid: " + std::to_string(isValid));
	
	if(!isValid)
			return false;
	
	a.logStr("MATCH: " + std::to_string(cPos.getX()) + " " + std::to_string(cPos.getY()));
	
	if(!hasMoved)
		hasMoved = true;
	
	if(game->getPiece(cPos) != nullptr)
		game->getPiece(cPos)->die();
	
	pos = cPos;
	
	return true;
}

Pos Piece::getPos()
{
	return pos;
}

bool Piece::isDead()
{
	return dead;
}

void Piece::die()
{
	dead = false;
}

bool Piece::isWhite() const
{
	return white;
}

char Piece::getCharacter() const
{
	return chr;
}
