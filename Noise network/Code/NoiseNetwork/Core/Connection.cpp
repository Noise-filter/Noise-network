#include "Connection.h"

Connection::Connection()
{
	address = "";
	port = 0;
	connected = false;
}

Connection::Connection(SOCKET socket)
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

Connection::~Connection()
{}

bool Connection::Connect(std::string address, unsigned short port)
{
	this->address = address;
	this->port = port;

	//Try to initialize socket if it isn't already initialized
	if (!socket.IsInitialized())
	{
		if (!socket.Init(AF_INET, SOCK_STREAM, IPPROTO_TCP))
		{
			return false;
		}
	}

	//Try to connect
	bool result = socket.Connect(address, port);

	connected = result;

	return result;
}

bool Connection::Reconnect()
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

bool Connection::Disconnect()
{
	if (connected)
	{
		socket.Shutdown(SD_SEND);
		socket.Close();
		connected = false;
	}

	return true;
}

int Connection::Send(std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Send(buffer, bufLength);
	}

	return 0;
}

int Connection::Recv(std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Recv(buffer, bufLength);
	}

	return 0;
}

unsigned short Connection::GetPort()
{
	return port;
}

std::string Connection::GetAddress()
{
	return address;
}