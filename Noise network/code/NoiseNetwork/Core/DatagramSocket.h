#ifndef DATAGRAM_SOCKET_H
#define DATAGRAM_SOCKET_H

#include "WinsockIncludes.h"
#include <vector>

class DatagramSocket
{
public:
	DatagramSocket();
	virtual ~DatagramSocket();

	bool Init(int family);

	bool Bind(unsigned short port);

	void Close();

	int Send(std::string ip, unsigned short port, std::vector<char>& buffer, int bufLength);
	int Recv(std::string ip, unsigned short port, std::vector<char>& buffer, int bufLength);

	int Send(const sockaddr_in address, std::vector<char>& buffer, int bufLength);
	int Recv(sockaddr_in& address, std::vector<char>& buffer, int bufLength);

	bool IsInitialized();

	SOCKET GetSocket();

private:
	SOCKET socket;

};

#endif