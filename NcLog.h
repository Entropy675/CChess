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
	void logStrP(std::string, int ll);
	void logStr(std::string, int ll);
	void add(std::string in);
	void post(int ll = 1);
	static void setLogLevel(int);
	
	private:
	static int logLevel;
	static std::string builder;
	WINDOW* pwin;

};

#endif
