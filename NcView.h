#ifndef NCVIEW_H
#define NCVIEW_H

#include "View.h"
#include "Board.h"

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>

class NcView : View
{
	public:
	NcView(Board*); // must subscribe to a Board on creation
	virtual ~NcView();
	
	virtual void update() override;
	virtual void toggleSize() override; // large/small
	virtual void userInput(std::string&) override;
	virtual void printAt(int x, int y, const std::string& s) const override;
	
	private:
	void initNcurses();
	void cleanupNcurses();	
	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is
	
	bool largeBoard = false;
	void wideChessConversion(char ch, bool isWhite, cchar_t& c);
	
	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
};


#endif
