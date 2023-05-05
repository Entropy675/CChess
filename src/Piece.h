#ifndef PIECE_H
#define PIECE_H

#include <vector>

#include "defs.h"
#include "NcLog.h"

#include "Pos.h"
#include "Board.h"
class MoveBehaviour;
class PawnMove;
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
	bool isValidMove(const Pos p);
	void validMoves(std::vector<Pos>& p);
	bool move(const Pos);

	bool isWhite() const;
	bool isDead() const;
	bool hasMoved() const;
	
	void die();
	
	std::string toString() const;
	Pos getPos() const;
	char getCharacter() const;
	Board* getBoard() const;
	
	PawnMove* getPawnBehaviour() const;
	void addBehav(MoveBehaviour*);

	protected:
	Pos pos;

	bool moved;
	bool dead;
	char chr; // {R, N, B, K, Q, P} -> {Rook, Knight, Bishop, King, Queen, Pawn}
	const bool white;

	std::vector<MoveBehaviour*> movebehavArr; // delegate isValidMove & validMoves to the sum of all these
	Board* game;
};

#endif