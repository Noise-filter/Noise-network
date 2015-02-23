#include "StreamConnection.h"

StreamConnection::StreamConnection()
{
	address = "";
	port = 0;
	connected = false;
}

StreamConnection::StreamConnection(SOCKET socket)
{
	this->socket = StreamSocket(socket);
	if (socket != INVALID_SOCKET)
	{
		connected = true;

		//Get the ip address and port
	}
	else
	{
		address = "";
		port = 0;
		connected = false;
	}
}

StreamConnection::~StreamConnection()
{}

bool StreamConnection::Connect(std::string address, unsigned short port)
{
	this->address = address;
	this->port = port;

	//Try to initialize socket if it isn't already initialized
	if (!socket.IsInitialized())
	{
		if (!socket.Init(AF_INET))
		{
			return false;
		}
	}

	//Try to connect
	//bool result = socket.Connect(address, port);

	//connected = result;

	return 0;
}

bool StreamConnection::Reconnect()
{
	//Return true if already connected
	if (connected)
	{
		return true;
	}

	//Only try to reconnect if connect has already been called 
	if (port != 0 && address != "")
	{
		return Connect(this->address, this->port);
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

int StreamConnection::Send(std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Send(buffer, bufLength);
	}

	return 0;
}

int StreamConnection::Recv(std::vector<char>& buffer, int bufLength)
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

unsigned short StreamConnection::GetPort()
{
	return port;
}

std::string StreamConnection::GetAddress()
{
	return address;
}