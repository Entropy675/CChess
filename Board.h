#ifndef BOARD_H
#define BOARD_H
#include "defs.h"
#include "Pos.h"
#include "Piece.h"
#include "pieces/Pawn.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"

class Board
{
	public:
	
	Board();
	
	
	bool whiteTurn;
	
	void setStartingBoard(bool startingColor);
	void drawBoard();
	void toggleSize(); // large/small
	void cleanBoard();
	
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is
	
	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
	
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL]; // remember to free later
	
	private:
	bool largeBoard = false;
};

#endif
