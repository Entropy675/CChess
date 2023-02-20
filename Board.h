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
	
	void setStartingBoard(bool flag, std::vector<Piece*>* whitePieces, std::vector<Piece*>* blackPieces);
    void movePiece(Pos, Pos); // move from a to b if valid on this piece
    Piece* getPiece(Pos);
    
    private:
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL];
	bool refreshEPPawns;
};



#endif
