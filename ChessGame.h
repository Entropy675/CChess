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
	View* view; // TODO: Turn this into a vector of view pointers. Change code to work with list of views.
	Board* game;
};

#endif
