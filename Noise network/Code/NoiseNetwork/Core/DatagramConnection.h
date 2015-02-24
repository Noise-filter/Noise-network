#ifndef DATAGRAM_CONNECTION_H
#define DATAGRAM_CONNECTION_H

#include "DatagramSocket.h"

class DatagramConnection
{
public:
	DatagramConnection();
	virtual ~DatagramConnection();

	//If bindAddress port == 0, the socket will bind on the same port found in the addr parameter.
	bool Connect(SocketAddress addr, SocketAddress bindAddress = SocketAddressFactory::Create("0.0.0.0", 0));

	void Disconnect();

	int Send(std::vector<char>& buffer, int bufLength);
	int Recv(SocketAddress addr, std::vector<char>& buffer, int bufLength);

	bool IsConnected();
	SocketAddress GetAddress();

private:
	DatagramSocket socket;

	SocketAddress addr;
	bool connected;

};

#endif