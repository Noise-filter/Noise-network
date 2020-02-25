#ifndef DATAGRAM_SOCKET_H
#define DATAGRAM_SOCKET_H

#include "WinsockIncludes.h"
#include <vector>
#include "SocketAddress.h"

class DatagramSocket
{
public:
	DatagramSocket();

	bool Init(int family);

	bool Bind(SocketAddressInterface& bindAddress);

	void Close();

	int Send(SocketAddressInterface& address, std::vector<unsigned char>& buffer, int bufLength);
	int Recv(SocketAddressInterface& address, std::vector<unsigned char>& buffer, int bufLength);

	bool IsInitialized();

	SOCKET GetSocket();

private:
	SOCKET socket;

};

#endif