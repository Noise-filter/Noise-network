#include "HttpClient.h"

#include "Utilities/StringUtils.h"

using namespace std;

HttpClient::HttpClient()
{
}

HttpClient::HttpClient(SocketAddress host)
{
	SetHost(host);
}

HttpClient::HttpClient(const std::string& httpAddress, unsigned short port)
{
	SetHost(httpAddress, port);
}

HttpClient::~HttpClient()
{}

void HttpClient::SetHost(SocketAddress host)
{
	this->host = host;
}

void HttpClient::SetHost(const std::string& httpAddress, unsigned short port)
{
	string host;
	unsigned short tempPort;

	string protocol = toLowerCase(httpAddress.substr(0, 8));
	if (protocol.substr(0, 7) == "http://")
	{
		host = httpAddress.substr(7);
		tempPort = port != 0 ? port : 80;
	}
	else if (protocol == "https://")
	{
		host = httpAddress.substr(8);
		tempPort = port != 0 ? port : 443;
	}
	else
	{
		host = httpAddress;
		tempPort = port != 0 ? port : 80;
	}

	if (!host.empty() && (*host.rbegin() == '/'))
	{
		host.erase(host.end()-1);
	}

	hostName = host;

	this->host = SocketAddressFactory::Create(host, tempPort);
}

HttpResponse HttpClient::SendRequest(const HttpRequest& request)
{
	HttpRequest toSend = CorrectRequest(request);

	HttpResponse response;

	if (connection.Connect(host))
	{
		string requestStr = toSend.GetRequestAsString();
		vector<char> sendBuffer(requestStr.begin(), requestStr.end());

		if (!sendBuffer.empty())
		{
			if (connection.Send(sendBuffer, sendBuffer.size()) != -1)
			{
				vector<char> recvBuffer(1024);
				string receivedStr;
				int bytesReceived = 0;
				while ((bytesReceived = connection.Recv(recvBuffer, 1024)) > 0)
				{
					receivedStr.append(recvBuffer.begin(), recvBuffer.begin() + bytesReceived);
				}

				response.parse(receivedStr);
			}
		}
		connection.Disconnect();
	}

	return response;
}

HttpRequest HttpClient::CorrectRequest(const HttpRequest& request)
{
	HttpRequest toSend(request);

	if (!toSend.HasField("From"))
	{
		toSend.SetField("From", "testingUser");
	}
	if (!toSend.HasField("User-Agent"))
	{
		toSend.SetField("From", "testingUser");
	}
	if (!toSend.HasField("Host"))
	{
		toSend.SetField("Host", hostName);
	}
	if (!toSend.HasField("Content-Length"))
	{
		toSend.SetField("From", "testingUser");
	}
	if (toSend.getMethod() == HttpMethod::POST && !toSend.HasField("Content-Type"))
	{
		toSend.SetField("Content-Type", "application/x-www-form-urlencoded");
	}
	if ((toSend.getVersion().getMajorVersion() * 10 + toSend.getVersion().getMinorVersion() >= 11) 
		&& !toSend.HasField("Connection"))
	{
		toSend.SetField("Connection", "close");
	}

	return toSend;
}

SocketAddress HttpClient::GetHost()
{
	return host;
}

std::string HttpClient::GetHostname()
{
	return hostName;
}