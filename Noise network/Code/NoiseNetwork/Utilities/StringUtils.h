#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <algorithm>
#include <string>

std::string toLowerCase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string toUpperCase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

#endif