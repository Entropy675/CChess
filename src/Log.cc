#include "Log.h"
#include "View.h"

std::string Log::message = "";
std::vector<View*> Log::views;

Log::Log(int locallog) : logLevelLocal(locallog) {}
Log::~Log(){}

void Log::addView(View* v)
{
	views.push_back(v); // could make some assumptions about the order of the view but we won't for future compatibility
}

View* Log::delViewById(int id)
{
	long unsigned int i;
	for(i = 0; i < views.size(); ++i)
		if(views[i]->getId() == id)
			break;
	if(i == views.size()) return nullptr;
	View* retV  = views[i];
	views.erase(views.begin() + i);
	return retV;
}
	
void Log::append(std::string in) 
{
	if(logLevelLocal > LOG_LEVEL) // if the local log object is higher then the global, don't log
		return;
	message += in;
}

void Log::appendLine(std::string in)
{
	if(logLevelLocal > LOG_LEVEL) 
		return;
	message += in + "\n";
}

void Log::setLogLevel(int a)
{
	if(a < 1) // cannot allow less then 1 log level, to avoid bypassing program wide log level of 0
		return;

	logLevelLocal = a;
}

void Log::flush()
{
	if(message == "")
		return;
	
	message += "\n";
	for(long unsigned int i = 0; i < views.size(); ++i)
		views[i]->log(message);
	message = "";
}

void Log::logStr(std::string s)
{
	if(logLevelLocal > LOG_LEVEL)
		return;
	
	s += "\n";
	for(long unsigned int i = 0; i < views.size(); ++i)
		views[i]->log(s);
}
