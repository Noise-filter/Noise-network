#ifndef DATAGRAM_CONNECTION_H
#define DATAGRAM_CONNECTION_H

#include "DatagramSocket.h"

class DatagramConnection
{
public:
	DatagramConnection();

	//If bindAddress port == 0, the socket will bind on the same port found in the addr parameter.
	bool Connect(const std::shared_ptr<SocketAddressInterface>& addr, SocketAddressInterface& bindAddress = *SocketAddressFactory::Create("0.0.0.0", 0));

	void Disconnect();

	int Send(std::vector<unsigned char>& buffer, int bufLength);
	int Recv(std::vector<unsigned char>& buffer, int bufLength);

	bool IsConnected();
	const SocketAddressInterface& GetAddress();

private:
	DatagramSocket socket;

	std::shared_ptr<SocketAddressInterface> addr;
	bool connected;

};

#endif