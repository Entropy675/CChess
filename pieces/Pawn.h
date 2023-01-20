#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Pos.h"
#include "defs.h"
#include <vector>

class Pawn : Piece
{
	bool isValidMove(Pos p) override
	{
		// we can assume the input pos is a valid pos (check for pos before)
		// (invalid positions cannot be saved in a pos variable)
		
		
		
	}
	
	void validMoves(std::vector<Pos> * p) override
	{
		
	}
	
	void move(Pos p) override
	{
		
	}
	
}




#endif
