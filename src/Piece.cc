#include "Piece.h"
#include "MoveBehaviour.h"
#include "piece_behav/PawnMove.h"
#include "piece_behav/CrossMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/KnightMove.h"
#include "piece_behav/KingMove.h"

#include <cctype>

Piece::Piece(Pos p, char c, bool w, Board* g) 
	: enPassantActive(false), pos(p), moved(false), dead(false), chr(c), white(w), game(g) {}

// piece cleans up its behaviour array
Piece::~Piece() 
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		delete movebehavArr[i];
}

ChessStatus Piece::move(Pos cPos)
{
	Log log(3);
	bool isValid = false;
	Bitboard moves = validMoves();
	ChessStatus returnChessStatus = ChessStatus::FAIL;

	bool previousEpOnBoard = game->isEnpassantOnBoard();
	game->epDeactivate(); // deactivate enpassant check, if needed it will be reactivated by validMoves' pawn behavior
	
	PawnMove* pm = getPawnBehaviour();
	if(pm != nullptr)
	{
		returnChessStatus = ChessStatus::PAWNMOVE;
		
		isValid = pm->enPassantCheckAct(cPos, *this); // Act refers to instantly killing enpassant target when true
		if(isValid)
			log.append("EP CHECK ACT PASS\n");
		
		if(cPos.getY() == MAX_ROW_COL-1 || cPos.getY() == 0)
			returnChessStatus = ChessStatus::PROMOTE;
	}

	if(moves[cPos])
		isValid = true;
	

	if(isValid) // legal move!
	{
		// If pawn is moving up 2 squares ...
		if(pm != nullptr && Pos(getPos().getX(), getPos().getY() + (isWhite() ? -1 : 1)*2) == cPos)
		{
			// ... set the left and right pawn to enpassant this one (if they exist).
			pm->EPValidateTarget(this, true);
			pm->EPValidateTarget(this, false);
		}
		
		if(!moved)
			moved = true;
		
		log.append(" ======= ---*^\\> MATCH: " + cPos.toString() + "\n");
		pos = cPos; // ***change the position of the piece***
		
		if(returnChessStatus == ChessStatus::FAIL)
			returnChessStatus = ChessStatus::SUCCESS; // PROMOTE stays the same, flips FAIL
	}
	else
	{	
		if(previousEpOnBoard) // reset to the previous enpassant value
			game->epActivate(); 
		else
			game->epDeactivate();
		
		
		return ChessStatus::FAIL; // if returnChessStatus = PROMOTE but its illegal, this is where it FAILs.
	}
	return returnChessStatus;
}

Bitboard Piece::validMoves(Pos* p) const
{
	Bitboard moves;
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		moves = moves | ((p == nullptr) ? movebehavArr[i]->validMoves() : movebehavArr[i]->validMoves(p));
	return moves;
}

Bitboard Piece::validCaptures(Pos* p) const
{
	Bitboard moves;
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		moves = moves | ((p == nullptr) ? movebehavArr[i]->validCaptures() : movebehavArr[i]->validCaptures(p));
	return moves;
}

bool Piece::isValidMove(const Pos p)
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		if(movebehavArr[i]->isValidMove(p))
			return true;
	return false;
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

std::string Piece::getBoardPos() const
{
	Log log(2);
	
	std::string out = "";
	
	out += "abcdefgh"[pos.getX()]; // Pos class can only hold values between 0-7, so no mem issues!
	out += std::to_string(MAX_ROW_COL - pos.getY());
	
	log.append("EnPassant Target: " + out + "\n");
	return out; // pos string
}

std::string Piece::toString() const
{
	std::string r = "Piece [";
	r += chr;
	r += "]:, is ";
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

void Piece::clearAllBehavs()
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++) // usually a piece will have either 1 or 2 behaviors... not slow under this condition.
		delete movebehavArr[i];
	movebehavArr.clear();
}
	
PawnMove* Piece::getPawnBehaviour() const
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		if(PawnMove* pawnMove = dynamic_cast<PawnMove*>(movebehavArr.at(i)))
			return pawnMove;
	return nullptr;
}

KingMove* Piece::getKingBehaviour() const
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		if(KingMove* kingMove = dynamic_cast<KingMove*>(movebehavArr.at(i)))
			return kingMove;
	return nullptr;
}

void Piece::addBehav(MoveBehaviour* b)
{
	b->setFrom(this);
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

void Piece::die(bool clear)
{
	dead = true;
	if(clear)
		game->clearPiece(pos); // clear the piece ptr off the game board
}

void Piece::setDead(bool a)
{
	dead = a;
}

bool Piece::isWhite() const
{
	return white;
}

char Piece::getCharacter() const
{
	return chr;
}

bool Piece::hasMoved() const
{
	return moved;
}

const Pos& Piece::getPos() const
{
	return pos;
}
