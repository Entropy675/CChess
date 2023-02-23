#include "NcLog.h"

std::string NcLog::builder = "";
int NcLog::logLevel = 0;

NcLog::NcLog()
{
	pwin = newwin(5, 30, 5, 20);
}

NcLog::~NcLog()
{
	delwin(pwin);
    endwin();
}

void NcLog::add(std::string in)
{
	if(builder != "")
		builder += "  ";
	builder += in;
}

void NcLog::setLogLevel(int a)
{
	logLevel = a;
}

void NcLog::post(int ll)
{
	logStr(builder, ll);
	builder = "";
}

void NcLog::logStrP(std::string s, int ll)
{
	if(logLevel < ll)
		return;
	
    box(pwin, 0, 0);
    mvwprintw(pwin, 2, 1, "%s", s.c_str());
    wrefresh(pwin);
    getch();
}

void NcLog::logStr(std::string s, int ll)
{
	if(logLevel < ll)
		return;
	
    WINDOW *popup = newwin(15, s.length()+4, 1, 20);
    mvwprintw(popup, 2, 2, "%s", s.c_str());
    box(popup, 0, 0);
    wrefresh(popup);
    getch();

    delwin(popup);
    endwin();
}

