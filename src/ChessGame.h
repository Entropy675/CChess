#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include <cstring>
#include <regex>
#include <iostream>
#include <vector>

#include "Board.h"
#include "View.h"
#include "Log.h"

class ChessGame
{
	public:
	ChessGame(View* = nullptr, View* = nullptr);
	~ChessGame();

	void startLocalNcursesGame(); // main control flow, for running directly.
	
	
	// Starting to build API...
	void addView(View*);
	void updateAllSpectators();
	

	private:
	
	View* whitePlayer;
	View* blackPlayer;
	std::vector<View*> otherViews;
	Board* game;
};

#endif
