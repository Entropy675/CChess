#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <string>

#include "defs.h"
#include "Log.h"

#include "Pos.h"
#include "Board.h"
class MoveBehaviour;
class PawnMove;
class KingMove;
//#include "MoveBehaviour.h" this is always used as a ptr so it can all be linked
//#include "piece_behav/PawnMove.h"

/*
** Piece
** Reperesents a single piece on the chess board. Holds all the attributes of
** the chess piece, including a list of pointers to movement behaviour and a character
** indicating the type of the piece.
** {R, N, B, K, Q, P} -> {Rook, Knight, Bishop, King, Queen, Pawn} as per standard.
*/
class Piece
{
	friend std::ostream& operator<<(std::ostream&, const Piece&);
	
	public:
	Piece(Pos p, char c = '0', bool w = false, Board* g = nullptr);
	~Piece();
	

	ChessStatus move(const Pos);
	Board* getBoard() const;

	bool isValidMove(const Pos p);
	void validMoves(std::vector<Pos>& p);
	Bitboard validMoves(Pos* = nullptr) const;
	Bitboard validCaptures(Pos* = nullptr) const;
	
	bool isWhite() const;
	bool isDead() const;
	bool hasMoved() const;
	
	const Pos& getPos() const;
	std::string toString() const;
	std::string getBoardPos() const;
	
	void promote(const char);
	void epActivate();
	void die(bool = false);
	void setDead(bool);
	
	char toFENChar() const;
	char getCharacter() const;
	
	PawnMove* getPawnBehaviour() const;
	KingMove* getKingBehaviour() const;
	void addBehav(MoveBehaviour*);

	protected:
	void clearAllBehavs();
	
	bool enPassantActive;
	Pos pos;
	
	bool moved;
	bool dead;
	char chr; // {R, N, B, K, Q, P} -> {Rook, Knight, Bishop, King, Queen, Pawn}
	const bool white;

	std::vector<MoveBehaviour*> movebehavArr; // delegate isValidMove & validMoves to the sum of all these
	Board* game;
};

#endif
