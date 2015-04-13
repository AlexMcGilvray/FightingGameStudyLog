#include "Utilities.h" 
#include <fstream>  
#include <vector>
#include <stdarg.h>
 
namespace Utilities
{  
	std::string  GetFormattedStringImplementation(const char *fmt, va_list ap);
	  
	const char * GetTextFileContents(const char * filename)
	{
		std::ifstream t;
		int length;
		t.open(filename);      // open input file
		t.seekg(0, std::ios::end);    // go to the end
		length = t.tellg();           // report location (this is the length)
		t.seekg(0, std::ios::beg);    // go back to the beginning
		char * buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension
		t.read(buffer, length);       // read the whole file into the buffer
		buffer[t.gcount()] = 0;
		t.close(); 
		return buffer;
	}  
  
	std::string GetFormattedString (const char *fmt, ...)
	{
		va_list ap;
		va_start (ap, fmt);
		std::string buf = GetFormattedStringImplementation (fmt, ap);
		va_end (ap);
		return buf;
	}
	//This function is courtesy of Larry Gritz from this stack overflow page : 
	//http://stackoverflow.com/questions/69738/c-how-to-get-fprintf-results-as-a-stdstring-w-o-sprintf#69911
	//Uses the BSD license. Quote from the post : "This code is part of an open source project that I'm writing (BSD license), so everybody feel free to use this as you wish."
	std::string  GetFormattedStringImplementation(const char *fmt, va_list ap)
	{
		// Allocate a buffer on the stack that's big enough for us almost
		// all the time.  Be prepared to allocate dynamically if it doesn't fit.
		size_t size = 1024;
		char stackbuf[1024];
		std::vector<char> dynamicbuf;
		char *buf = &stackbuf[0]; 
		while (1) {
			// Try to vsnprintf into our buffer.
			int needed = vsnprintf (buf, size, fmt, ap);
			// NB. C99 (which modern Linux and OS X follow) says vsnprintf
			// failure returns the length it would have needed.  But older
			// glibc and current Windows return -1 for failure, i.e., not
			// telling us how much was needed. 
			if (needed <= (int)size && needed >= 0) {
				// It fit fine so we're done.
				return std::string (buf, (size_t) needed);
			} 
			// vsnprintf reported that it wanted to write more characters
			// than we allotted.  So try again using a dynamic buffer.  This
			// doesn't happen very often if we chose our initial size well.
			size = (needed > 0) ? (needed+1) : (size*2);
			dynamicbuf.resize (size);
			buf = &dynamicbuf[0];
		}
	}
}
