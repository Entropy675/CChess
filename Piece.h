#ifndef PIECE_H
#define PIECE_H

#include <ncurses.h>
#include <vector>

#include "defs.h"
#include "Pos.h"
#include "Board.h"

#include "NcLog.h"

class Piece 
{
	public:
	Piece(Pos p, char c = '0', bool w = false, Board* g = nullptr);
	
    virtual ~Piece();
    virtual bool isValidMove(Pos p) = 0; // virtual meaning it can be overriden, = 0 meaning it must be.
	virtual void validMoves(std::vector<Pos>& p) = 0;
	virtual bool move(Pos);
	
	bool isWhite() const;
	char getCharacter();
	bool isDead();
	void die();
	
	Pos getPos();

    protected:
    Pos pos;
    
    bool hasMoved;
    bool dead;
    char chr; // {R, N, B, K, Q, P} -> {Rook, Knight, Bishop, King, Queen, Pawn}
    const bool white;
    
    Board* game;
};

#endif
