#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "defs.h"
#include "Pos.h"
#include "Piece.h"
#include "NcLog.h"

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
	bool largeBoard;
	
	NcView* view;
	Board* game;
};

#endif
