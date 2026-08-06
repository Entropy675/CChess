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
	void setEmptyBoard(bool whiteToMove);              // custom-position setup (sibling of setStartingBoard)
	Piece* placePiece(int x, int y, char type, bool white); // place + wire behaviour on a custom board
	bool registerPromotion(std::string&);

	bool isMoveValidOnKing(bool, Piece&, Pos, Pos);
	
    void disableCheck();
	bool isCheckOnBoard() const;

	bool isCheckmate();
	bool isStalemate();
	// const: reads the attack maps after refreshing them, and that refresh is a
	// memoized cache update (see the mutable maps below), not a state change.
	// isCheckmate/isStalemate/sideToMoveHasLegalMove are deliberately NOT const:
	// they route through isMoveValidOnKing, which SIMULATES a move by mutating
	// gameBoard and restoring it. That is logically const but genuinely mutating,
	// so const there would be a lie -- and it would hide a real hazard, since two
	// threads querying the same board would corrupt each other's simulation.
	bool sideToMoveInCheck() const;
	bool sideToMoveHasLegalMove();
	bool sideToMoveHasLegalEnPassant();
	
	const Piece& getWhiteKing() const;
	const Piece& getBlackKing() const;
	
	bool isWhiteTurn() const;
	bool isWhitePerspective() const; // use this to determine weather to draw the board flipped
	int getMoves() const;
	
	int getTurnFEN() const;
	std::string toFENString() const;
	bool loadFEN(const std::string& fen); // inverse of toFENString (CChess FEN convention)

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
	// const + mutable maps: this is a memoization cache refresh, which is the
	// textbook case for mutable. It recomputes a view OF the position rather than
	// changing the position, so a const query that needs fresh maps can call it.
	void updateMaps() const;
	ChessStatus tryCastle(Pos kingSq, Pos rookSq); // king moving onto its own unmoved rook
	bool castleRight(bool white, bool kingside) const; // FEN castling right, derived from live state
	
	std::vector<Piece*>* whitePieces;
	Piece* whiteKing;
	bool whiteCheck;
	
	std::vector<Piece*>* blackPieces;
	Piece* blackKing;
	bool blackCheck;

	mutable Bitboard whiteAttackMap;
	mutable Bitboard blackAttackMap;
	mutable Bitboard whiteMoveMap;
	mutable Bitboard blackMoveMap;
	
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
