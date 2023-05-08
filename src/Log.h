#ifndef NCLOG_H
#define NCLOG_H

#include <string>
#include <vector>

// set higher for more logs, 1 means basic logs, >1 is more specific. 0 = no logs.
#define LOG_LEVEL		2
/*
// BASIC LOG_LEVEL USAGE (for this project)
// 0 - NO LOGS. Set to 0 to have no logs at all.
// 1 - BASIC LOGS. This shows basic information about each move after it is made.
// 2 - MOVE LOGS. This shows every move considered in the log.
// 3 - PIECE SPECIFIC LOGS. This shows logs specific to certain pieces.
// The higher you go, the more logs you get. There shouldn't be much after this though.
*/


class Log
{
	public:
	Log(int = 1);
	virtual ~Log();
	
	/*
	// Append and logStr are based off of the global LOG_LEVEL, which is the level at which you want the message to show up.
	// If both the local log level is under the LOG_LEVEL, the message will show up.
	// The message can be built up across any Log object, the moment it is flushed it will show. This prevents any possible
	// message loss, and it also allows for a more flexable use of the Log object.
	// The default LOG_LEVEL is defined above.
	// The local log level must be defined per log object, with setLogLevel. Default is 1.
	// WARNING: Don't think you can log inside of const functions, they are supposed to be side-effect free, logging cannot be so.
	*/
	
	virtual void logStr(std::string) = 0; // in case you just want to log something straight up, no shenanigans, not recommended.
	
	// setLogLevel() set the local objects log level. Default is 1, can be set on creation of object (so you don't really need this often).
	// [==>   append() allows you to build up a log message. Only appends if the log level matches (adds new line at end).
	// [==>   flush() writes all logs saved up to the screen.
	// *----- these two functions are the key to this class.
	virtual void setLogLevel(int = 1) = 0;
	virtual void append(std::string in) = 0;
	virtual void flush() = 0;
	
	private:
	int logLevelLocal;
	static std::string message;
};

#endif
