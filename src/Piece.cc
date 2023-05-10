#include "Piece.h"
#include "MoveBehaviour.h"
#include "piece_behav/PawnMove.h"
#include "piece_behav/CrossMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/KnightMove.h"

#include <cctype>

Piece::Piece(Pos p, char c, bool w, Board* g) 
	: pos(p), moved(false), dead(false), chr(c), white(w), game(g) {}

// piece cleans up its behaviour array
Piece::~Piece() 
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		delete movebehavArr[i];
}

std::string Piece::getBoardPos() const
{
	std::string out = "" + "abcdefgh"[pos.getX()]; // Pos class can only hold values between 0-7, so no mem issues!
	out += std::to_string(pos.getY() + 1);
	return out; // pos string
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

void Piece::epActivate()
{
	game->epActivate();
}

char Piece::toFENChar() const // all chars are stored in uppercase
{
	if(white)
		return chr;
	return std::tolower(chr);
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
	Log log(1);
	std::vector<Pos> p; 
	
	game->epDeactivate(); // deactivate enpassant check, if need be it will be reactivated by validMoves' pawn behavior
	log.append("EP bool is deactivated, weather used or not.");
	
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		movebehavArr[i]->validMoves(p, this); // sets EP check
	
	bool isValid = false;
	ChessStatus returnChessStatus = ChessStatus::FAIL;
	
	PawnMove* pm = getPawnBehaviour();
	if(pm != nullptr)
	{
		returnChessStatus = ChessStatus::PAWNMOVE;
		if(pm->enPassantCheckAct(cPos, *this)) // Act refers to instantly killing enpassant target when true
			isValid = true;
		if(cPos.getY() == MAX_ROW_COL-1 || cPos.getY() == 0)
			returnChessStatus = ChessStatus::PROMOTE; // assume its a PAWNMOVE (since only ones that promote)
	}
	
	log.append("CHESSSTATUS in PIECE: " + getChessStatusString(returnChessStatus) + "\n");
	log.setLogLevel(2);
	log.append("EP bool: set ");
	
	if(game->isEnpassantOnBoard())
		log.append("TRUE!");
	else
		log.append("FALSE!");
	log.append("\n");
	
	if(!isValid)
	{
		for(std::vector<Pos>::size_type i = 0; i < p.size(); i++)
		{
			if(p.at(i) == cPos)
			{
				isValid = true;
				if(returnChessStatus == ChessStatus::FAIL) // ensures that PROMOTE stays the same
					returnChessStatus = ChessStatus::SUCCESS;
				break;
			}
		}
	}
	
	log.setLogLevel(1);
	log.append("Valid: " + std::to_string(isValid) + "\n");
	log.append("to Pos: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()));
	for(long unsigned int i = 0; i < p.size(); i++)
		log.append(p[i].toString());
	
	if(isValid) // if isValid was never found, we don't move
	{
		log.append(" ======= ---*^\\> MATCH: " + std::to_string(cPos.getX()) + ", " + std::to_string(cPos.getY()) + "\n");
		if(!moved)
			moved = true;
		pos = cPos; 
	}
	else
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
