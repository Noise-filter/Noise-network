#include "DatagramSocket.h"

DatagramSocket::DatagramSocket()
{
	socket = INVALID_SOCKET;
}

DatagramSocket::~DatagramSocket()
{
	this->Close();
}

bool DatagramSocket::Init(int family)
{
	socket = ::socket(family, SOCK_DGRAM, IPPROTO_UDP);
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

bool DatagramSocket::Bind(SocketAddress bindAddress)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = bind(socket, (sockaddr*)*bindAddress, sizeof(sockaddr_in));
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void DatagramSocket::Close()
{
	closesocket(socket);
	socket = INVALID_SOCKET;
}

int DatagramSocket::Send(const SocketAddress address, std::vector<char>& buffer, int bufLength)
{
	int result = sendto(socket, &buffer[0], bufLength, 0, (sockaddr*)*address, sizeof(sockaddr_in));
	return result;
}

int DatagramSocket::Recv(SocketAddress address, std::vector<char>& buffer, int bufLength)
{
	int fromLen = sizeof(sockaddr_in);
	int result = recvfrom(socket, &buffer[0], bufLength, 0, (sockaddr*)*address, &fromLen);
	return result;
}

bool DatagramSocket::IsInitialized()
{
	return (socket != INVALID_SOCKET);
}

SOCKET DatagramSocket::GetSocket()
{
	return socket;
}