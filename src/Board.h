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

	void disableCheck();
	void setStartingBoard(bool = true);
	bool registerPromotion(std::string&);

	ChessStatus movePiece(Pos, Pos); // move from a to b if valid on this piece
	Piece* getPiece(Pos) const;
	void clearPiece(Pos);
		
	const Piece& getWhiteKing() const;
	const Piece& getBlackKing() const;
	
	bool isWhiteTurn() const;
	int getMoves() const;
	
	int getTurnFEN() const;
	std::string toFENString() const;

	std::string getEnPassantBoardPosFEN() const;
	bool isEnpassantOnBoard() const;
	void epActivate();
	void epDeactivate();
	
	void updateWhiteBlackChecks();
	// TODO: overload [] and/or [][] for the board interface
	
	std::vector<Piece*>* getWhitePieces() const;
	std::vector<Piece*>* getBlackPieces() const;
	const Bitboard& getWhiteAttackMap() const;
	const Bitboard& getBlackAttackMap() const;

	private:
	char promotionMatchChar(std::string&);
	void updateAttackMaps();
	
	std::vector<Piece*>* whitePieces;
	Piece* whiteKing;
	bool whiteCheck;
	bool whiteCastleKS;
	bool whiteCastleQS;
	
	std::vector<Piece*>* blackPieces;
	Piece* blackKing;
	bool blackCheck;
	bool blackCastleKS;
	bool blackCastleQS;

	Bitboard whiteAttackMap;
	Bitboard blackAttackMap;
	
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
