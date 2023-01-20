#ifndef BOARD_H
#define BOARD_H
#include "defs.h"
#include "Pos.h"
#include "Piece.h"

class Board
{
	public:
	
	Board();
	
	void drawBoard();
	void toggleSize(); // large/small
	
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is
	
	Piece* gameBoard[MAX_ARR_SIZE]; // remember to free later
	
	private:
	bool largeBoard = false;
};

#endif
