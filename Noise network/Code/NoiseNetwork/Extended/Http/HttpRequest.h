#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <map>

#include "HttpUtilities.h"
#include "ParseException.h"

class HttpRequest
{
public:
	HttpRequest(const std::string& uri = "/", const HttpMethod method = GET, const std::string& body = "");
	~HttpRequest();

	std::string GetRequestAsString();

	std::string GetUri() const;
	std::string GetBody() const;
	HttpMethod getMethod() const;
	unsigned int getMajorVersion() const;
	unsigned int getMinorVersion() const;
	std::string GetField(const std::string& key) const;
	bool HasField(const std::string& key) const;

	void SetUri(const std::string& uri);
	void SetBody(const std::string& body);
	void SetMethod(const HttpMethod method);
	void SetHttpVersion(const unsigned int majorVersion, const unsigned int minorVersion);
	void SetField(const std::string& key, const std::string& value);
	void SetFieldTable(const FieldTable& fields);

private:
	std::string uri;
	std::string body;
	HttpMethod method;

	//TODO: Change versions to it's own class
	unsigned int majorVersion;
	unsigned int minorVersion;

	FieldTable fields;

};

#endif