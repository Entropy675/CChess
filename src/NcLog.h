#ifndef NCLOG_H
#define NCLOG_H

#include <string>
#include <vector>
#include <ncurses.h>

// set higher for more logs, 1 means basic logs, >1 is more specific. 0 = no logs.
#define LOG_LEVEL		1  
/*
// BASIC LOG DECORM (for this project)
// 0 - NO LOGS. Set to 0 to have no logs at all.
// 1 - BASIC LOGS. This shows basic information about each move after it is made.
// 2 - MOVE LOGS. This shows every move considered in the log.
// 3 - PIECE SPECIFIC LOGS. This shows logs specific to certain pieces.
*/


class NcLog
{
	public:
	NcLog(int locallog = 1);
	~NcLog();
	
	/*
	// Append and logStr require a log level, which is the level at which you want the message to show up.
	// If both the local log level and the global log level are high enough, then the message will pass through.
	// The default global log level is defined above.
	// The local log level must be defined per log object, with setLogLevel. Default is 1.
	*/
	
	// logs in a new unique popup, for any message input
	void logStr(std::string, int ll = 1); 
	
	// set the local objects log level. Default is 1.
	void setLogLevel(int);
	
	// append() allows you to build up a log message. Only appends if the log level matches (adds new line at end).
	// flush() writes all logs saved up to the screen.
	void append(std::string in, int ll = 1);
	void flush();
	
	private:
	// Private function to log the message and clear the internal message buffer.
	// Should not ever be called directly by users of the class.
	void logStrP(std::string);
	
	int logLevelLocal;
	static int logLevel;
	static std::string message;
	WINDOW* pwin;
};

#endif
