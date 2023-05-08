#ifndef NCVIEW_H
#define NCVIEW_H

#include "View.h"
#include "Board.h"

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>

class NcView : public View
{
	public:
	NcView(Board*); // must subscribe to a Board on creation
	virtual ~NcView();

	virtual void update() override;
	virtual void toggleSize() override; // large/small
	virtual void userInput(std::string&) override;
	virtual void print(const std::string& s) override;
	virtual void log(std::string) override;
	
	void printAt(int x, int y, const std::string& s) const;
	
	private:
	void logStrP(std::string);
	
	void initNcurses();
	void cleanupNcurses();
	void moveToInputPos() const;

	void drawBoard();
	void drawPieces();
	void drawPieceBar();

	void wideChessConversion(char ch, bool isWhite, cchar_t& c);

	Pos sqSize; // size of a singe square on board
	Pos offset; // offset of where the center of that square is

	// line characters for drawing board
	cchar_t li;
	cchar_t ld;
	
	WINDOW* logwin;
	const int baseWriteHead;
	int writeHead;
};


#endif
