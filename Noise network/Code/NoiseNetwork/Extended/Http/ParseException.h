#ifndef PARSE_EXCEPTION_H
#define PARSE_EXCEPTION_H

#include <exception>

class ParseException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Unexpected error while parsing";
	}
};

#endif