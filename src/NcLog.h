#ifndef NCLOG_H
#define NCLOG_H

#include <string>
#include <vector>
#include "Log.h"

#include <ncurses.h>

// Ncurses implementation of Log class
class NcLog : public Log
{
	public:
	NcLog(int locallog = 1);
	~NcLog();
	
	// See Log class for detailed usage instructions.
		
	virtual void logStr(std::string) override; 
	
	virtual void setLogLevel(int = 1) override;
	virtual void append(std::string) override;
	virtual void flush() override;
	
	private:
	void logStrP(std::string);
	
	int logLevelLocal;
	static std::string message;
	WINDOW* pwin;
};

#endif
