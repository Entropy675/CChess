#ifndef NCLOG_H
#define NCLOG_H

#include <string>
#include <vector>
#include <ncurses.h>

class NcLog
{
	public:
	NcLog();
	~NcLog();
	void logStrP(std::string);
	void logStr(std::string);
	
	private:
	WINDOW* pwin;

};

#endif
