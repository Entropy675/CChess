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

ChessStatus Piece::move(Pos cPos)
{
	Log log(1);
	bool isValid = false;
	ChessStatus returnChessStatus = ChessStatus::FAIL;
	bool onSuccessDeactivateEP = false;
	
	if(game->isEnpassantOnBoard())
	{
		onSuccessDeactivateEP = true;
		game->epDeactivate(); // deactivate enpassant check, if need be it will be reactivated by validMoves' pawn behavior
	}
	
	Bitboard moves = validMoves();
	PawnMove* pm = getPawnBehaviour();
	
	if(pm != nullptr)
	{
		returnChessStatus = ChessStatus::PAWNMOVE;
		
		isValid = pm->enPassantCheckAct(cPos, *this); // Act refers to instantly killing enpassant target when true
		if(isValid)
			log.append("EP CHECK ACT PASS\n");
		
		if(Pos(getPos().getX(), getPos().getY() + (isWhite() ? -1 : 1)*2) == cPos)
		{
			if(!hasMoved() && game->getPiece(Pos(getPos().getX(), getPos().getY() + (isWhite() ? -1 : 1))) == nullptr && game->getPiece(Pos(getPos().getX(), getPos().getY() + (isWhite() ? -1 : 1)*2)) == nullptr)
			{
				pm->EPValidateTarget(this, true);
				pm->EPValidateTarget(this, false);
			}
		}

		
		if(cPos.getY() == MAX_ROW_COL-1 || cPos.getY() == 0)
			returnChessStatus = ChessStatus::PROMOTE; // PROMOTE is PAWNMOVE because only pawns promote
	}

	if(moves[cPos])
		isValid = true; // you cant set isValid = moves[cPos] because isValid might already be true
	
	log.setLogLevel(1);
	log.append("CHESSSTATUS in PIECE: " + getChessStatusString(returnChessStatus) + "\n");
	log.append("Valid: " + std::to_string(isValid) + "\n");
	log.append("to Pos: " + cPos.toString() + " | ");
	std::vector<Pos> pVec; 
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		movebehavArr[i]->validMoves(pVec, this);
	for(long unsigned int i = 0; i < pVec.size(); i++)
		log.append(pVec[i].toString());
	log.append("\n");

	if(isValid) // if isValid was never found, we don't move
	{
		log.append(" ======= ---*^\\> MATCH: " + cPos.toString() + "\n");
		if(!moved)
			moved = true;
		pos = cPos; 
		if(returnChessStatus == ChessStatus::FAIL) // ensures that PROMOTE stays the same
			returnChessStatus = ChessStatus::SUCCESS;
	}
	else
	{	
		if(onSuccessDeactivateEP)
			game->epActivate(); // reactivate it since it failed
		else
			game->epDeactivate(); // in case the failed move wrongly activated it
		return ChessStatus::FAIL;
	}
	return returnChessStatus;
}

Bitboard Piece::validMoves()
{
	Bitboard moves;
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		moves = moves | movebehavArr[i]->validMoves(this);
	return moves;
}

Bitboard Piece::validCaptures()
{
	Bitboard moves;
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
	{
		if(PawnMove* pawnMove = dynamic_cast<PawnMove*>(movebehavArr.at(i)))
			moves = moves | pawnMove->validPawnCaptures(this);
		else
			moves = moves | movebehavArr[i]->validMoves(this);
	}
	return moves;
}

bool Piece::isValidMove(const Pos p)
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
		if(movebehavArr[i]->isValidMove(p, this))
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

void Piece::clearAllBehavs()
{
	for(long unsigned int i = 0; i < movebehavArr.size(); i++)
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

bool Piece::hasMoved() const
{
	return moved;
}

Pos Piece::getPos() const
{
	return pos;
}
