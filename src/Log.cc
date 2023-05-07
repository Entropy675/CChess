#include "Log.h"

std::string Log::message = "";
int Log::logLevel = LOG_LEVEL;

Log::Log(int locallog) : logLevelLocal(locallog) {}
Log::~Log(){}