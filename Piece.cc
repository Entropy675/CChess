#include "Piece.h"
#include "MoveBehaviour.h"
#include "piece_behav/PawnMove.h"

Piece::Piece(Pos p, char c, bool w, Board* g) 
	: pos(p), moved(false), dead(false), chr(c), white(w), game(g) {}

// piece cleans up its behaviour array
Piece::~Piece() 
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		delete movebehavArr[i];
}

bool Piece::move(Pos cPos)
{
	std::vector<Pos> p;
	
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		movebehavArr[i]->validMoves(p, this);
	
	NcLog a(1);
	
	bool isValid = false;
	
	PawnMove* pm = getPawnBehaviour();
	if(pm != nullptr)
		if(pm->enPassantCheckAct(cPos, *this)) // this instantly kills enpassant target when true
			isValid = true;
	
	if(!isValid)
	{
		for(std::vector<Pos>::size_type i = 0; i < p.size(); i++)
		{
			if(p.at(i) == cPos)
			{
				isValid = true;
				break;
			}
		}
	}
		
	a.append("Valid: " + std::to_string(isValid) + "\n");
	a.append("to Pos: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()));
	
	
	if(!isValid)
		return false;
	
	a.append(" ======= ---*^\\> MATCH: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()) + "\n");

	if(!moved)
		moved = true;

	pos = cPos; 
	
	return true;
}

bool Piece::hasMoved() const
{
	return moved;
}

Pos Piece::getPos() const
{
	return pos;
}

PawnMove* Piece::getPawnBehaviour() const
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		if(PawnMove* pawnMove = dynamic_cast<PawnMove*>(movebehavArr.at(i)))
			return pawnMove;
	return nullptr;
}

void Piece::addBehav(MoveBehaviour* b)
{
	return movebehavArr.push_back(b);
}

Board* Piece::getBoard() const
{
	return game;
}

bool Piece::isDead() const
{
	return dead;
}

void Piece::die()
{
	dead = true;
	game->clearPiece(pos); // clear the piece ptr off the game board
}

bool Piece::isWhite() const
{
	return white;
}

char Piece::getCharacter() const
{
	return chr;
}
