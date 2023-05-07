#include "Piece.h"
#include "MoveBehaviour.h"
#include "piece_behav/PawnMove.h"
#include "piece_behav/CrossMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/KnightMove.h"

Piece::Piece(Pos p, char c, bool w, Board* g) 
	: pos(p), moved(false), dead(false), chr(c), white(w), game(g) {}

// piece cleans up its behaviour array
Piece::~Piece() 
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		delete movebehavArr[i];
}

std::string Piece::toString() const
{
	std::string r = getCharacter() + ": " + getPos().toString() + ", is ";
	if(!dead)
		r += "not ";
	r += "dead.";
	return r;
}

std::ostream& operator<<(std::ostream& o, const Piece& p)
{
	o << p.toString();
	return o;
}

void Piece::promote(const char c)
{
	switch(c)
	{
		case 'r':
			clearAllBehavs();
			this->chr = 'R';
			addBehav(new PlusMove());
			break;
		case 'n':
			clearAllBehavs();
			this->chr = 'N';
			addBehav(new KnightMove());
			break;
		case 'b':
			clearAllBehavs();
			this->chr = 'B';
			addBehav(new CrossMove());
			break;
		case 'q':
			clearAllBehavs();
			this->chr = 'Q';
			addBehav(new CrossMove());
			addBehav(new PlusMove());
			break;
	}
	
}

void Piece::clearAllBehavs()
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		delete movebehavArr[i];
	movebehavArr.clear();
}
	
ChessStatus Piece::move(Pos cPos)
{
	NcLog a(1);
	std::vector<Pos> p; 
	
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		movebehavArr[i]->validMoves(p, this);
	
	bool isValid = false;
	ChessStatus returnChessStatus = ChessStatus::FAIL;
	
	PawnMove* pm = getPawnBehaviour();
	if(pm != nullptr)
	{
		if(pm->enPassantCheckAct(cPos, *this)) // Act refers to instantly killing enpassant target when true
		{
			NcLog hmm(1);
			hmm.append("EPCA active");
			hmm.flush();
			isValid = true;
			returnChessStatus = ChessStatus::SUCCESS;
		}
		if(cPos.getY() == MAX_ROW_COL-1 || cPos.getY() == 0) //
			returnChessStatus = ChessStatus::PROMOTE;
	}
	
	if(!isValid)
	{
		for(std::vector<Pos>::size_type i = 0; i < p.size(); i++)
		{
			if(p.at(i) == cPos)
			{
				isValid = true;
				if(returnChessStatus == ChessStatus::FAIL) // ensures that PROMOTE stays the same
				{
					returnChessStatus = ChessStatus::SUCCESS;
				}
				break;
			}
		}
	}
		
	a.append("Valid: " + std::to_string(isValid) + "\n");
	a.append("to Pos: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()));
	for(long unsigned int i = 0; i < p.size(); i++)
	{
		a.append(p[i].toString());
	}
	
	if(isValid) // if isValid was never found, we don't move
	{
		a.append(" ======= ---*^\\> MATCH: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()) + "\n");
		if(!moved)
			moved = true;
		pos = cPos; 
	}
	else
		if(returnChessStatus == ChessStatus::PROMOTE)
			return ChessStatus::FAIL;
	
	return returnChessStatus;
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
