#ifndef HTTP_VERSION_H
#define HTTP_VERSION_H

#include <iostream>

class HttpVersion
{
public:
	HttpVersion(unsigned int majorVersion = 0, unsigned int minorVersion = 0);
	~HttpVersion();

	unsigned int getMajorVersion() const;
	unsigned int getMinorVersion() const;

	void setVersion(const unsigned int majorVersion, const unsigned int minorVersion);

	friend bool operator ==(const HttpVersion& v1, const HttpVersion& v2);

	friend std::ostream& operator <<(std::ostream& out, const HttpVersion& version);
	friend std::istream& operator >>(std::istream& in, HttpVersion& version);

private:
	unsigned int majorVersion;
	unsigned int minorVersion;

};

#endif