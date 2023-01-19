#ifndef PIECE_H
#define PIECE_H


#include "Pos.h"

class Piece 
{
  public:
    Pos pos;
    bool isWhite;
    bool isCaptured;
    cchar_t chr;
    
    virtual bool isValidMove(int x, int y) = 0; // virtual meaning it can be overriden, = 0 meaning it must be.
    virtual void move(int x, int y) = 0;
};

#endif
