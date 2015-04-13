#pragma once 
#include <string>

namespace Utilities
{
	const char * GetTextFileContents(const char * filename);
	std::string GetFormattedString (const char *fmt, ...);
}
 