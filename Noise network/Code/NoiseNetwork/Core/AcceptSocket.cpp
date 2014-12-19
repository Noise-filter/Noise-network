#include "AcceptSocket.h"

AcceptSocket::AcceptSocket()
{
	
}

AcceptSocket::~AcceptSocket()
{
	Close();
}

bool AcceptSocket::Init(unsigned short port)
{
	bool result = socket.Init(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (!result)
	{
		return result;
	}

	result = socket.Bind(port);
	if (!result)
	{
		Close();
		return result;
	}

	result = socket.Listen();
	if (!result)
	{
		Close();
		return result;
	}

	return result;
}

SOCKET AcceptSocket::Accept()
{
	return socket.Accept();
}

void AcceptSocket::Close()
{
	socket.Close();
}

bool AcceptSocket::IsInitialized()
{
	return socket.IsInitialized();
}

SOCKET AcceptSocket::GetSocket()
{
	return socket.GetSocket();
}