#include "AcceptSocket.h"

#include "StreamConnection.h"

bool AcceptSocket::Init(SocketAddressInterface& bindAddress)
{
	bool result = socket.Init(bindAddress.GetFamily());
	if (!result)
	{
		return result;
	}

	result = socket.Bind(bindAddress);
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

StreamConnection AcceptSocket::Accept()
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