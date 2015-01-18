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

bool DatagramSocket::Bind(unsigned short port)
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

void DatagramSocket::Close()
{
	closesocket(socket);
	socket = INVALID_SOCKET;
}

int DatagramSocket::Send(std::string ip, unsigned short port, std::vector<char>& buffer, int bufLength)
{
	int result;
	return result;
}

int DatagramSocket::Recv(std::string ip, unsigned short port, std::vector<char>& buffer, int bufLength)
{
	int result;
	return result;
}

int DatagramSocket::Send(const sockaddr_in address, std::vector<char>& buffer, int bufLength)
{
	int result = sendto(socket, &buffer[0], bufLength, 0, (sockaddr*)&address, sizeof(sockaddr_in));
	return result;
}

int DatagramSocket::Recv(sockaddr_in& address, std::vector<char>& buffer, int bufLength)
{
	int fromLen = sizeof(address);
	int result = recvfrom(socket, &buffer[0], bufLength, 0, (sockaddr*)&address, &fromLen);
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