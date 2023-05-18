#ifndef BOARD_H
#define BOARD_H

#include "defs.h"
#include "Pos.h"
#include "Bitboard.h"
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

	void setStartingBoard(bool = true);
	bool registerPromotion(std::string&);

	ChessStatus movePiece(Pos, Pos); // move from a to b if valid on this piece
	Piece* getPiece(Pos) const;
	void clearPiece(Pos);

	bool isWhiteTurn() const;
	int getMoves() const;
	int getTurnFEN() const;
	std::string toFENString() const;

	std::string getEnPassantBoardPos() const;
	bool isEnpassantOnBoard() const;
	void epActivate();
	void epDeactivate();
		
	// TODO: overload [] and/or [][] for the board interface
	
	std::vector<Piece*>* getWhitePieces() const;
	std::vector<Piece*>* getBlackPieces() const;
	Bitboard getWhiteAttackMap() const;
	Bitboard getBlackAttackMap() const;

	private:
	char promotionMatchChar(std::string&);

	std::vector<Piece*>* whitePieces;
	bool whiteCastleKS;
	bool whiteCastleQS;
	std::vector<Piece*>* blackPieces;
	bool blackCastleKS;
	bool blackCastleQS;

	bool enPassantActive;

	Piece* previousPiece; // last piece moved
	Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL];
	
	bool whitePerspective; // for which way to display the board, display board flipped for black (nothing to do with gamelogic, only view)
	bool whiteTurn;
	
	int halfmoveCount;
	int turnCountFEN;
	int moveCount;
};


#endif
