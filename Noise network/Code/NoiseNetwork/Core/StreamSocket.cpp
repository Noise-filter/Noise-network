#include "StreamSocket.h"
#include "SocketAddressIPv4.h"
StreamSocket::StreamSocket()
{
	socket = INVALID_SOCKET;
	addr = nullptr;
}

StreamSocket::StreamSocket(SOCKET socket)
{
	this->socket = socket;

	//TODO: Get address from socket and put it in the SocketAddressInterface
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

bool StreamSocket::Connect(SocketAddress addr)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = connect(socket, (sockaddr*)*addr, sizeof((sockaddr)*addr));
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	this->addr = addr;

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
	addr = nullptr;
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

	//TODO: Get address from socket and put it in the SocketAddressInterface
}

SOCKET StreamSocket::GetSocket()
{
	return socket;
}