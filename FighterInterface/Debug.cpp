#include "Debug.h"

using namespace Debug;

namespace
{
	std::vector<LogEntry> logData;
}

int CalculateIndexFromEndOfVector(int idx);

int CalculateIndexFromEndOfVector(int idx) 
{
	return logData.size() - 1 - idx ;
}

 
std::string Debug::Logger::GetLogEntryText(int idx /*= 0*/) 
{
	int calcIdx = CalculateIndexFromEndOfVector(idx);
	if (calcIdx > 0)
	{
		return logData[logData.size() - 1 - idx].text;
	}
	else
	{
		return "Requested invalid log index. Check to make sure the index is valid vis Logger.IsValidIdx(int) to make sure you are requesting a log entry that exists";
	}
}

void Debug::Logger::Log(std::string entry)
{
	LogEntry logEntry;
	logEntry.text = entry;
	logData.push_back(logEntry);
}

bool Debug::Logger::LogEntryIndexExists(int idx)
{
	int calcIdx = CalculateIndexFromEndOfVector(idx);
	if (calcIdx > 0)
		return true;
	else 
		return false;
}

void Debug::Logger::LogAppend(std::string entry)
{
	logData[logData.size() - 1].text = logData[logData.size() - 1].text + entry;
}
