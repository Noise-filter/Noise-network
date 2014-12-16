#include "Socket.h"

Socket::Socket()
{
	socket = INVALID_SOCKET;
}


Socket::Socket(SOCKET socket)
{
	this->socket = socket;
}

Socket::~Socket()
{
	this->Close();
}

bool Socket::Init(int family, int type, int protocol)
{
	socket = ::socket(family, type, protocol);
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

bool Socket::Connect(const char* address, unsigned short port)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	struct hostent* hostent;

	//TODO: gethostbyname() is depricated, change it to getaddrinfo
	hostent = gethostbyname(address);
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

	//Connection successful!
	return true;
}

bool Socket::Bind(unsigned short port)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	//TODO: Change it to getaddrinfo
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

bool Socket::Listen()
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

SOCKET Socket::Accept()
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

bool Socket::Shutdown(int flag)
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

void Socket::Close()
{
	closesocket(socket);
}

bool Socket::IsInitialized()
{
	return (socket != INVALID_SOCKET);
}

void Socket::SetSocket(SOCKET socket)
{
	this->socket = socket;
}

SOCKET Socket::GetSocket()
{
	return socket;
}