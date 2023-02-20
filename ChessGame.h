#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"
#include "NcView.h"

class ChessGame
{
	public:
	ChessGame();
	~ChessGame();
	
	void startGame();	
	int bCharToInt(char);
	
	private:
	std::vector<Piece*>* whitePieces;
	std::vector<Piece*>* blackPieces;
	
	bool whiteTurn;
	bool largeBoard;
	
	NcView* view;
	Board* game;
};

#endif
