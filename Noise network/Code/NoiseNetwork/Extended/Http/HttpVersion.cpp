#include "HttpVersion.h"

using namespace std;

HttpVersion::HttpVersion(unsigned int majorVersion, unsigned int minorVersion)
	: majorVersion(majorVersion), minorVersion(minorVersion)
{}

HttpVersion::~HttpVersion()
{}

unsigned int HttpVersion::getMajorVersion() const
{
	return majorVersion;
}

unsigned int HttpVersion::getMinorVersion() const
{
	return minorVersion;
}

void HttpVersion::setVersion(const unsigned int majorVersion, const unsigned int minorVersion)
{
	this->majorVersion = majorVersion;
	this->minorVersion = minorVersion;
}

bool operator ==(const HttpVersion& v1, const HttpVersion& v2)
{
	return (v1.majorVersion == v2.majorVersion &&
			v1.minorVersion == v2.minorVersion);
}

ostream& operator <<(ostream& out, const HttpVersion& version)
{
	out << version.majorVersion << '.' << version.minorVersion;
	return out;
}

istream& operator >>(istream& in, HttpVersion& version)
{
	char temp;
	in >> version.majorVersion >> temp >> version.minorVersion;
	return in;
}