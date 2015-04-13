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

	namespace DebuggingOptions
	{
		//Character state debugging
		bool State_JumpForwardDebugging = false;
		bool State_JumpBackwardDebugging = false;


		//TODO : Add a function to load debugging options from a file
	};
};

