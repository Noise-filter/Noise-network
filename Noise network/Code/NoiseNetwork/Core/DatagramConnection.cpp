#include "DatagramConnection.h"

DatagramConnection::DatagramConnection()
{

}

DatagramConnection::~DatagramConnection()
{

}

bool DatagramConnection::Connect(std::string address, unsigned short port)
{

	return false;
}

void DatagramConnection::Disconnect()
{

}

int DatagramConnection::Send(std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		//return sendto(socket.GetSocket(), &buffer[0], bufLength, 0, , sizeof(sockaddr_in));
	}
	return -1;
}

int DatagramConnection::Recv(std::vector<char>& buffer, int bufLength)
{
	if (connected)
	{
		//return recvfrom(socket.GetSocket(), &buffer[0], bufLength, 0, , sizeof(sockaddr_in));
	}
	return -1;
}

bool DatagramConnection::IsConnected()
{
	return connected;
}

unsigned short DatagramConnection::GetPort()
{
	return port;
}

std::string DatagramConnection::GetAddress()
{
	return address;
}