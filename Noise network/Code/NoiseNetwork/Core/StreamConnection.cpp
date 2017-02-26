#include "StreamConnection.h"

StreamConnection::StreamConnection()
{
	connected = false;
}

StreamConnection::StreamConnection(SOCKET socket)
{
	this->socket = StreamSocket(socket);
	if (socket != INVALID_SOCKET)
	{
		connected = true;
	}
	else
	{
		connected = false;
	}
}

StreamConnection::StreamConnection(SOCKET socket, SocketAddress addr)
{
	this->socket = StreamSocket(socket, addr);
	if (socket != INVALID_SOCKET)
	{
		connected = true;
	}
	else
	{
		connected = false;
	}
}

StreamConnection::~StreamConnection()
{}

bool StreamConnection::Connect(SocketAddress addr)
{
	//Try to initialize socket if it isn't already initialized
	if (!socket.IsInitialized())
	{
		if (!socket.Init(addr->GetFamily()))
		{
			return false;
		}
	}

	//Try to connect
	bool result = socket.Connect(addr);

	connected = result;

	return connected;
}

bool StreamConnection::Reconnect()
{
	//Return true if already connected
	if (connected)
	{
		return true;
	}

	//Only try to reconnect if connect has already been called 
	if (socket.GetAddress())
	{
		return Connect(socket.GetAddress());
	}
	
	return false;
}

bool StreamConnection::Disconnect()
{
	if (connected)
	{
		socket.Shutdown(SD_SEND);
		socket.Close();
		connected = false;
	}

	return true;
}

int StreamConnection::Send(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Send(buffer, bufLength);
	}

	return 0;
}

int StreamConnection::Recv(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Recv(buffer, bufLength);
	}

	return 0;
}

bool StreamConnection::IsConnected()
{
	return connected;
}

StreamSocket StreamConnection::GetSocket()
{
	return socket;
}