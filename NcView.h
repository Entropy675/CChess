#ifndef NCVIEW_H
#define NCVIEW_H

#include "Board.h"

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>

class NcView
{
	public:
	NcView(Board*, std::vector<Piece*>* whitePieces, std::vector<Piece*>* blackPieces);
	void drawBoard();
	void toggleSize(); // large/small
	void userInput(std::string&);
	void initNcurses();
	void cleanupNcurses();
	void asciiChessConversion(char ch, bool isWhite, cchar_t& c);
    
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is
	
	private:
	Board* game;
	
	std::vector<Piece*>* whitePieces;
	std::vector<Piece*>* blackPieces;
	
	bool largeBoard = false;
	
	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
};


#endif
