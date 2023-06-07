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
	
	
	// proxy class overloads [] operator for the [][] operation.
	class Proxy 
	{
		private:
		Piece* const* row;
		
		public:
		Proxy(Piece* const* rowData) : row(rowData) {}
		
		Piece* operator[](int col) const {
			return row[col];
		}
	};
	
	Proxy operator[](int row) const; // proxy allows for [] operator.
	Piece* operator[](Pos) const;
	Piece* operator()(int row, int col) const;
	

	Board();
	~Board();

	ChessStatus movePiece(Pos, Pos); // move from a to b if valid on the piece at the first position
	Piece* getPiece(Pos) const;
	void clearPiece(Pos);
	
	void setStartingBoard(bool = true);
	bool registerPromotion(std::string&);

	bool isMoveValidOnKing(bool, Piece&, Pos, Pos);
	
	void disableCheck();
	bool isCheckOnBoard() const;
	
	const Piece& getWhiteKing() const;
	const Piece& getBlackKing() const;
	
	bool isWhiteTurn() const;
	bool isWhitePerspective() const; // use this to determine weather to draw the board flipped
	int getMoves() const;
	
	int getTurnFEN() const;
	std::string toFENString() const;

	std::string getEnPassantBoardPosFEN() const;
	bool isEnpassantOnBoard() const;
	void epActivate();
	void epDeactivate();
	
	
	std::vector<Piece*>* getWhitePieces() const;
	std::vector<Piece*>* getBlackPieces() const;
	const Bitboard& getWhiteAttackMap() const;
	const Bitboard& getBlackAttackMap() const;
	const Bitboard& getWhiteMoveMap() const;
	const Bitboard& getBlackMoveMap() const;

	Bitboard getWhiteAttackMap(const Piece& p, Pos* to, bool includePiecesAttacks = true) const;
	Bitboard getBlackAttackMap(const Piece& p, Pos* to, bool includePiecesAttacks = true) const;
	Bitboard getWhiteMoveMap(const Piece& p, Pos* to, bool includePiecesAttacks = true) const;
	Bitboard getBlackMoveMap(const Piece& p, Pos* to, bool includePiecesAttacks = true) const;

	private:
	
	template <typename Function>
	Bitboard conditionalGetMap(const Piece& p, Pos* to, bool includePiecesAttacks, Function func, std::vector<Piece*>* pieces) const;

	char promotionMatchChar(std::string&);
	void updateMaps();
	
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
	Bitboard whiteMoveMap;
	Bitboard blackMoveMap;
	
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
