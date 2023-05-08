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
	bool registerPromotion(std::string&);
	void clearPiece(Pos);

	std::string toFENString() const;
	bool isWhiteTurn() const;
	int getTurn() const;
	Piece* getPiece(Pos) const;
	
	
	void epActivate();
	void epDeactivate();
	bool isEnpassantOnBoard() const;
	
	ChessStatus movePiece(Pos, Pos); // move from a to b if valid on this piece
	
	// TODO: overload [] and/or [][] for the board interface
	
	std::vector<Piece*>* getWhitePieces() const;
	std::vector<Piece*>* getBlackPieces() const;

	private:
	char promotionMatchChar(std::string&);

	std::vector<Piece*>* whitePieces;
	bool whiteCastleKS;
	bool whiteCastleQS;
	std::vector<Piece*>* blackPieces;
	bool blackCastleKS;
	bool blackCastleQS;

	bool enPassantActive;

	Piece* promotePiece; // last piece moved
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL];
	bool whiteTurn;
	int halfmoveCount;
	int turnCount;
	
};


#endif
