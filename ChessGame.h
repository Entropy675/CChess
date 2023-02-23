#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include <cstring>
#include <regex>
#include <iostream>

#include "Board.h"
#include "NcView.h"

#include "NcLog.h"

class ChessGame
{
	public:
	ChessGame();
	~ChessGame();
	
	void startGame();
	
	private:
	bool largeBoard;
	
	NcView* view;
	Board* game;
};

#endif
