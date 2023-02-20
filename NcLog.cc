#include "NcLog.h"
#include <string>
#include <ncurses.h>

NcLog::NcLog() : builder("")
{
	pwin = newwin(5, 30, 5, 20);
}

void NcLog::add(std::string in)
{
	if(builder != "")
		builder += "  ";
	builder += in;
}

void NcLog::post()
{
	logStr(builder);
	builder = "";
}

NcLog::~NcLog()
{
	delwin(pwin);
    endwin();
}

void NcLog::logStrP(std::string s)
{
    box(pwin, 0, 0);
    mvwprintw(pwin, 2, 1, "%s", s.c_str());
    wrefresh(pwin);
    getch();
}

void NcLog::logStr(std::string s)
{

    WINDOW *popup = newwin(15, s.length()+4, 1, 20);
    mvwprintw(popup, 2, 2, "%s", s.c_str());
    box(popup, 0, 0);
    wrefresh(popup);
    getch();

    delwin(popup);
    endwin();
}

