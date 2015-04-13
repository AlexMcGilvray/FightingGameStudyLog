#include "Utilities.h" 
#include <fstream>  
 
namespace Utilities
{ 
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
}
