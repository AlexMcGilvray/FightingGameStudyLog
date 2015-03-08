#pragma once
#include <vector> 
#include <string>

namespace Debug
{ 
	 
	struct LogEntry
	{
		//const char * text; 
		std::string text;
	};
	
	namespace Logger
	{
		//todo include overloads that allow you to specify a range. Also maybe a percentage based param for scroll bars
		 std::string GetLogEntryText(int idx = 0);
		 bool LogEntryIndexExists(int idx);
		void Log(std::string entry); 
		void LogAppend(std::string entry);
	
	}; 
};

