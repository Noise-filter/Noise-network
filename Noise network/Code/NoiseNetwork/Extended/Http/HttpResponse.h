#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include <map>

#include "HttpUtilities.h"
#include "HttpVersion.h"

class HttpResponse
{
public:
	HttpResponse();
	~HttpResponse();

	const bool HasField(const std::string& key) const;
	const std::string& GetField(const std::string& key) const;
	HttpStatusCode GetStatus() const;
	HttpVersion GetVersion() const;
	const std::string& GetBody() const;

	void parse(const std::string& data);

private:
	void extractVersion(std::istringstream& in);
	void extractStatus(std::istringstream& in);
	bool isValidHttpVersion(const std::string& version);

private:
	FieldTable fields;
	HttpStatusCode status;
	HttpVersion version;
	std::string body;

};

#endif