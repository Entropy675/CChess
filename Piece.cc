#include "Piece.h"

Piece::Piece(Pos p, char c, bool w, Board* g) 
	: pos(p), hasMoved(false), dead(false), chr(c), white(w), game(g) {}

Piece::~Piece() {}

bool Piece::move(Pos cPos)
{
	std::vector<Pos> p;
	validMoves(p);
	
	NcLog a(1);
	
	bool isValid = false;
	
	for(std::vector<Pos>::size_type i = 0; i < p.size(); i++)
		if(p.at(i) == cPos)
			isValid = true;
			
	a.append("Valid: " + std::to_string(isValid) + "\n");
	a.append("to Pos: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()));
	
	
	if(!isValid)
		return false;
	
	a.append(" ======= ---*^\\> MATCH: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()) + "\n");

	if(!hasMoved)
		hasMoved = true;

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
	dead = true;
}

bool Piece::isWhite() const
{
	return white;
}

char Piece::getCharacter()
{
	return chr;
}
