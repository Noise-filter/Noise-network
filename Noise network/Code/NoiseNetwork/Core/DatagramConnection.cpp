#include "DatagramConnection.h"

DatagramConnection::DatagramConnection()
{
	addr = nullptr;
	connected = false;
}

bool DatagramConnection::Connect(const std::shared_ptr<SocketAddressInterface>& addr, SocketAddressInterface& bindAddress)
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

int DatagramConnection::Send(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Send(*addr, buffer, bufLength);
	}
	return 0;
}

int DatagramConnection::Recv(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Recv(*addr, buffer, bufLength);
	}
	return 0;
}

bool DatagramConnection::IsConnected()
{
	return connected;
}

const SocketAddressInterface& DatagramConnection::GetAddress()
{
	return *addr;
}