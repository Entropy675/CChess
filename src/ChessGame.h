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
	ChessGame(View* = nullptr, View* = nullptr); // takes ownership
	virtual ~ChessGame();
	
	// Starting to build API...
	void addView(View*);
	void updateAllSpectators();
	virtual void runLocalGame() = 0;

	protected:
	int localGameloop();
	
	View* whitePlayer;
	View* blackPlayer;
	std::vector<View*> otherViews;
	Board* game;
};

#endif
