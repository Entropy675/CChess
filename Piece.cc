#include "Piece.h"

#include "NcLog.h"

#include "pieces/Pawn.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"

Piece::Piece(Pos p, char c, bool w, Board* g) 
	: pos(p), clearEnPassantPiece{nullptr, nullptr}, hasMoved(false), dead(false), chr(c), white(w), game(g) {}

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
			
	a.add("Valid: " + std::to_string(isValid) + "\n");
	a.add("to Pos: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()));
	
	
	if(!isValid)
	{
		a.post();
		return false;
	}
	
	
	a.add(" ======= ---*^\\> MATCH: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()) + "\n");
	a.post();
	
	if(!hasMoved)
		hasMoved = true;
	
	if(game->getPiece(cPos) != nullptr)
		game->getPiece(cPos)->die();
	
	for(int i = 0; i < 2; i++)
	{
		if(clearEnPassantPiece[i] != nullptr)
		{
			a.add("Found removabale link? " + std::to_string(i) + "\n"); // test this to find bug
			//clearEnPassantPiece[i]->enPassantTarget(nullptr);
			//clearEnPassantPiece[i] = nullptr;
		}
	}
	
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
