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
	
	void setStartingBoard(bool flag);
    void movePiece(Pos, Pos); // move from a to b if valid on this piece
    bool isWhiteTurn();
    Piece* getPiece(Pos);
    void clearPiece(Pos);
    int getTurn();
    
	std::vector<Piece*>* whitePieces;
	std::vector<Piece*>* blackPieces;
    
    private:
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL];
	bool refreshEPPawns;
	bool whiteTurn;
	int turnCount;
};



#endif
