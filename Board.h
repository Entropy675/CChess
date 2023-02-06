#ifndef BOARD_H
#define BOARD_H
#include "defs.h"
#include "Pos.h"
#include "Piece.h"
#include <vector>
#include <string>

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
	~Board();
	bool whiteTurn;
	
	void userInput(std::string&);
	void setStartingBoard(bool);
	void drawBoard();
	void toggleSize(); // large/small
	
    void movePiece(Pos&, Pos&); // move from a to b if valid on this piece
    
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is
	
	private:
	
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	
	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
	
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL]; // remember to free later
	
	void cleanBoard();
	bool largeBoard = false;
};

#endif
