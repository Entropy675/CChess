#ifndef BOARD_H
#define BOARD_H
#include "defs.h"
#include "Pos.h"
#include "Piece.h"
#include <vector>

#include "pieces/Pawn.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"

/* Board
 * Contains all of the game-wide variables and code
 * also handles player turns and pieces, and the visual
 * aspects of the game.
 */
class Board
{
	public:
	
	Board();
	bool whiteTurn;
	
	void setStartingBoard(bool startingColor);
	void drawBoard();
	void toggleSize(); // large/small
	void cleanBoard();
	
    void movePiece(Pos&, Pos&); // move from a to b if valid on this piece
	
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	
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
