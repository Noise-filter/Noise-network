#ifndef DATAGRAM_SOCKET_H
#define DATAGRAM_SOCKET_H

#include "WinsockIncludes.h"
#include <vector>
#include "SocketAddressFactory.h"

class DatagramSocket
{
public:
	DatagramSocket();
	virtual ~DatagramSocket();

	bool Init(int family);

	bool Bind(SocketAddress bindAddress);

	void Close();

	int Send(const SocketAddress address, std::vector<char>& buffer, int bufLength);
	int Recv(SocketAddress address, std::vector<char>& buffer, int bufLength);

	bool IsInitialized();

	SOCKET GetSocket();

private:
	SOCKET socket;

};

#endif