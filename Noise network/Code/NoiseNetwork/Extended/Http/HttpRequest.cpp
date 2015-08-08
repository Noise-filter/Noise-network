#include "HttpRequest.h"

#include <sstream>

#include "Utilities/StringUtils.h"

static const char* const endLine = "\r\n";

HttpRequest::HttpRequest(const std::string& uri, const HttpMethod method, const std::string& body)
{
	SetUri(uri);
	SetHttpVersion(HttpVersion(1, 0));
	this->method = method;
	this->body = body;
}

HttpRequest::~HttpRequest()
{

}

std::string HttpRequest::GetRequestAsString()
{
	std::ostringstream out;

	std::string method = HttpMethodString[this->method];
	if (method.empty())
	{
		throw ParseException();
	}

	out << method << " " << uri << " ";
	out << "HTTP/" << version << endLine;

	for (const auto field : fields)
	{
		out << field.first << ": " << field.second << endLine;
	}
	out << endLine;

	out << body;

	return out.str();
}

std::string HttpRequest::GetUri() const
{
	return uri;
}

std::string HttpRequest::GetBody() const
{
	return body;
}

HttpMethod HttpRequest::getMethod() const
{
	return method;
}

HttpVersion HttpRequest::getVersion() const
{
	return version;
}

std::string HttpRequest::GetField(const std::string& key) const
{
	return fields.at(toLowerCase(key));
}

bool HttpRequest::HasField(const std::string& key) const
{
	return fields.find(toLowerCase(key)) != fields.end();
}

void HttpRequest::SetUri(const std::string& uri)
{
	this->uri = uri;

	// Make sure the uri starts with a '/'
	if (uri.empty() || uri.at(0) != '/')
	{
		this->uri.insert(0, "/");
	}
}

void HttpRequest::SetBody(const std::string& body)
{
	this->body = body;
}

void HttpRequest::SetMethod(const HttpMethod method)
{
	this->method = method;
}

void HttpRequest::SetHttpVersion(const HttpVersion& version)
{
	this->version = version;
}

void HttpRequest::SetField(const std::string& key, const std::string& value)
{
	this->fields[toLowerCase(key)] = value;
}

void HttpRequest::SetFieldTable(const FieldTable& fields)
{
	this->fields = fields;
}