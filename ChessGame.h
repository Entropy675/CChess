#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"

class ChessGame
{
	public:
	ChessGame();
	void startGame();
	int bCharToInt(char&);
	
	private:
	Board* game;
};

#endif
