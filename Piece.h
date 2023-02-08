#ifndef PIECE_H
#define PIECE_H

#include "defs.h"
#include <ncurses.h>
#include <vector>
#include "Pos.h"


class Piece 
{
	public:
	Piece();
    Pos pos;
    bool isWhite;
    bool hasMoved = false;
    bool dead = false;
    
    cchar_t chr;
    
    virtual ~Piece();
    virtual bool isValidMove(Pos p) = 0; // virtual meaning it can be overriden, = 0 meaning it must be.
	virtual void validMoves(std::vector<Pos>* p, Piece* (&gameBoard)[MAX_ROW_COL][MAX_ROW_COL]) = 0;
};

#endif
