#ifndef BOARD_H
#define BOARD_H
#include "defs.h"
#include "Pos.h"
#include "Piece.h"
#include <vector>
#include <string>

/* Board
 * Contains all of the game-wide variables and code
 * also handles player turns and pieces, and the visual
 * aspects of the game.
 */
class Board
{
	public:
	
	Board();
	~Board();
	
	bool whiteTurn;
	
	void setStartingBoard(bool);
    void movePiece(Pos&, Pos&); // move from a to b if valid on this piece
    
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is
	
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL]; // remember to free later
	
	void cleanBoard();
};

#endif
