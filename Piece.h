#ifndef PIECE_H
#define PIECE_H


#include <ncurses.h>
#include <vector>
#include "Pos.h"


class Piece 
{
  public:
    Pos pos;
    bool isWhite;
    bool isCaptured;
    bool hasMoved;
    
    cchar_t chr;

    virtual bool isValidMove(Pos p) = 0; // virtual meaning it can be overriden, = 0 meaning it must be.
	virtual void validMoves(std::vector<Pos>& p)  = 0;
    virtual void move(Pos p) = 0;
};

#endif
