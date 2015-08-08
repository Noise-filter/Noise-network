#include "HttpResponse.h"

#include <sstream>

#include "Utilities/StringUtils.h"
#include "ParseException.h"

HttpResponse::HttpResponse() : status(InvalidResponse), version(0, 0)
{}

HttpResponse::~HttpResponse()
{}

const bool HttpResponse::HasField(const std::string& key) const
{
	return fields.find(toLowerCase(key)) != fields.end();
}

const std::string& HttpResponse::GetField(const std::string& key) const
{
	return fields.at(toLowerCase(key));
}

HttpStatusCode HttpResponse::GetStatus() const
{
	return status;
}

HttpVersion HttpResponse::GetVersion() const
{
	return version;
}

const std::string& HttpResponse::GetBody() const
{
	return body;
}

void HttpResponse::parse(const std::string& data)
{
	std::istringstream in(data);

	try 
	{
		extractVersion(in);
		extractStatus(in);
	}
	catch (const ParseException& e)
	{
		return;
	}

	// Ignore the end of first line
	in.ignore(10000, '\n');

	// Parse the other lines, which contain fields, one by one
	std::string line;
	while (std::getline(in, line) && (line.size() > 2))
	{
		std::string::size_type pos = line.find(": ");
		if (pos != std::string::npos)
		{
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 2);

			if (!value.empty() && (*value.rbegin() == '\r'))
			{
				value.erase(value.size() - 1);
			}

			fields[toLowerCase(key)] = value;
		}
	}

	// Finally extract the body
	body.clear();
	std::copy(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), std::back_inserter(body));
}

void HttpResponse::extractStatus(std::istringstream& in)
{
	// Extract status code from the first line
	int status;
	if (in >> status)
	{
		this->status = static_cast<HttpStatusCode>(status);
	}
	else
	{
		status = InvalidResponse;
		throw ParseException();
	}
}

void HttpResponse::extractVersion(std::istringstream& in)
{
	//Extract HTTP version from the first line
	std::string version;
	if (in >> version)
	{
		if (isValidHttpVersion(version))
		{
			this->version.setVersion(version[5] - '0', version[7] - '0');
		}
		else
		{
			status = InvalidResponse;
			throw ParseException();
		}
	}
}

bool HttpResponse::isValidHttpVersion(const std::string& version)
{
	if ((version.size() >= 8) && (version[6] == '.') &&
		(toLowerCase(version.substr(0, 5)) == "http/") &&
		isdigit(version[5]) && isdigit(version[7]))
	{
		return true;
	}
	return false;
}