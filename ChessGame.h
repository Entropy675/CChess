#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"

class ChessGame
{
	public:
	ChessGame();
	
	void startGame();	
	int bCharToInt(char&);
	
	void userInput(std::string&);
	void drawBoard();
	void toggleSize(); // large/small
	
	
	private:
	
	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
	
	bool largeBoard = false;
	
	Board* game;
};

#endif
