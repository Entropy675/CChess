#include "NcLog.h"

std::string NcLog::message = "";

NcLog::NcLog(int locallog) : logLevelLocal(locallog)
{
	pwin = newwin(5, 30, 5, 20);
}

NcLog::~NcLog()
{
	delwin(pwin);
    endwin();
}

void NcLog::append(std::string in) // ll can be used to change each messages log leval (default 1)
{
	if(logLevelLocal > LOG_LEVEL) // if the local log object is higher then the global, don't log
		return;

	if(message != "")
		message += "  "; // 2 spaces: 1 account for popup boarder, 1 add space for visual appeal
	message += in;
}

void NcLog::setLogLevel(int a)
{
	if(a <= 1) // cannot allow less then 1 log level, to avoid bypassing program wide log level of 0
		return;

	logLevelLocal = a;
}

void NcLog::flush()
{
	if(message == "")
		return;

	logStrP(message);
	message = "";
}

void NcLog::logStr(std::string s)
{
	if(logLevelLocal > LOG_LEVEL)
		return;

	box(pwin, 0, 0);
	mvwprintw(pwin, 2, 1, "%s", s.c_str());
	wrefresh(pwin);
	getch();
}

void NcLog::logStrP(std::string s)
{
	WINDOW *popup = newwin(15, s.length()+4, 1, 20);
	mvwprintw(popup, 2, 2, "%s", s.c_str());
	box(popup, 0, 0);
	wrefresh(popup);
	getch();

	delwin(popup);
	endwin();
}
