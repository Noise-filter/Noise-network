#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "Core/StreamConnection.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpClient
{
public:
	HttpClient();
	HttpClient(SocketAddress host);
	HttpClient(const std::string& httpAddress, unsigned short port = 0);
	~HttpClient();

	void SetHost(SocketAddress host);
	void SetHost(const std::string& httpAddress, unsigned short port = 0);
	HttpResponse SendRequest(const HttpRequest& request);

	SocketAddress GetHost();
	std::string GetHostname();

private:
	HttpRequest CorrectRequest(const HttpRequest& request);

private:
	StreamConnection connection;
	SocketAddress host;
	std::string hostName;

};

#endif