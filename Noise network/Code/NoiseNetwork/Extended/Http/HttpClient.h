#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "Core/StreamConnection.h"

#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpClient
{
public:
	HttpClient();
	HttpClient(const std::shared_ptr<SocketAddressInterface>& host);
	HttpClient(const std::string& httpAddress, unsigned short port = 0);
	~HttpClient();

	void SetHost(const std::shared_ptr<SocketAddressInterface>& host);
	void SetHost(const std::string& httpAddress, unsigned short port = 0);
	HttpResponse SendRequest(const HttpRequest& request);

	std::shared_ptr<SocketAddressInterface> GetHost() const;
	std::string GetHostname() const;

private:
	HttpRequest CorrectRequest(const HttpRequest& request);

private:
	StreamConnection connection;
	std::shared_ptr<SocketAddressInterface> host;
	std::string hostName;

};

#endif