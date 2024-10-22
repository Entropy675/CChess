#ifndef NCVIEW_H
#define NCVIEW_H

#include "View.h"
#include "Board.h"
#include "Obfuscate/obfuscate.h"

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>

#include <iostream>
#include <fstream>

class NcView : public View
{
	public:
	NcView(Board* = nullptr); // must subscribe to a Board on creation
	virtual ~NcView();

	virtual void update() override;
	virtual void toggleSize() override; // large/small
	virtual void userInput(std::string&) override;
	virtual void print(const std::string&) override;
	virtual void log(const std::string&) override;
	
	void printAt(int x, int y, const std::string& s) const;
	
	private:
	void initNcurses();
	void cleanupNcurses();
	void moveToInputPos() const;

	void drawBoard();
	void drawPieces();
	void drawPieceBar();
	void drawCheckmate(bool white);

	void wideChessConversion(char ch, bool isWhite, cchar_t& c);

	int logwinX = 36;
	int logwinY = 0;
	int logwinWidth = 100;
	int logwinHeight = 20;	
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is

	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
	
	WINDOW* logwin;
	const int baseWriteHead;
	int writeHead;
	std::ofstream logfile;
	std::string logstring;
};


#endif
