#include "Lib.h"



bool Printer(std::string cString)
{
	std::string* lpcString = new std::string(cString);
	std::cout << *lpcString << std::endl;
	return true;
}
