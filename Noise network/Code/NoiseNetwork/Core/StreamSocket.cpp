#include "StreamSocket.h"

StreamSocket::StreamSocket()
{
	socket = INVALID_SOCKET;
}

StreamSocket::StreamSocket(SOCKET socket)
{
	this->socket = socket;
}

StreamSocket::~StreamSocket()
{
	this->Close();
}

bool StreamSocket::Init(int family)
{
	socket = ::socket(family, SOCK_STREAM, IPPROTO_TCP);
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

bool StreamSocket::Connect(std::string address, unsigned short port)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	struct hostent* hostent;

	//TODO: gethostbyname() is depricated, change it to getaddrinfo()
	hostent = gethostbyname(address.c_str());
	if (hostent == NULL)
	{
		return false;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = *(unsigned long*)hostent->h_addr;

	int result = connect(socket, (sockaddr*)&server, sizeof(server));
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	//StreamConnection successful!
	return true;
}

bool StreamSocket::Bind(unsigned short port)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	//TODO: Change it to getaddrinfo()
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	int result = bind(socket, (sockaddr*)&server, sizeof(server));
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool StreamSocket::Listen()
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = listen(socket, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

SOCKET StreamSocket::Accept()
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKET clientSocket = INVALID_SOCKET;

	clientSocket = accept(socket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		return INVALID_SOCKET;
	}

	return clientSocket;
}

bool StreamSocket::Shutdown(int flag)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = shutdown(socket, flag);
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void StreamSocket::Close()
{
	closesocket(socket);
	socket = INVALID_SOCKET;
}

int StreamSocket::Send(std::vector<char>& buffer, int bufLength)
{
	int result = send(socket, &buffer[0], bufLength, 0);
	return result;
}

int StreamSocket::Recv(std::vector<char>& buffer, int bufLength)
{
	int result = recv(socket, &buffer[0], bufLength, 0);
	return result;
}

bool StreamSocket::IsInitialized()
{
	return (socket != INVALID_SOCKET);
}

void StreamSocket::SetSocket(SOCKET socket)
{
	this->socket = socket;
}

SOCKET StreamSocket::GetSocket()
{
	return socket;
}