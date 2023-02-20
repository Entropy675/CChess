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
	void add(std::string in);
	void post();
	
	private:
	static std::string builder;
	WINDOW* pwin;

};

#endif
