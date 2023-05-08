#include "Log.h"

std::string Log::message = "";

Log::Log(int locallog) : logLevelLocal(locallog) {}
Log::~Log(){}