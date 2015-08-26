#include "DatagramConnection.h"

DatagramConnection::DatagramConnection()
{
	addr = nullptr;
	connected = false;
}

DatagramConnection::~DatagramConnection()
{
	Disconnect();
}

bool DatagramConnection::Connect(SocketAddress addr, SocketAddress bindAddress)
{
	this->addr = addr;

	if (!socket.IsInitialized())
	{
		if (!socket.Init(addr->GetFamily()))
		{
			return false;
		}

		if (!socket.Bind(bindAddress))
		{
			return false;
		}
	}

	connected = true;

	return true;
}

void DatagramConnection::Disconnect()
{
	connected = false;
	socket.Close();
}

int DatagramConnection::Send(std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Send(addr, buffer, bufLength);
	}
	return 0;
}

int DatagramConnection::Recv(SocketAddress addr, std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Recv(addr, buffer, bufLength);
	}
	return 0;
}

bool DatagramConnection::IsConnected()
{
	return connected;
}

SocketAddress DatagramConnection::GetAddress()
{
	return addr;
}