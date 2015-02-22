#ifndef DATAGRAM_CONNECTION_H
#define DATAGRAM_CONNECTION_H

#include "DatagramSocket.h"

class DatagramConnection
{
public:
	DatagramConnection();
	virtual ~DatagramConnection();

	bool Connect(std::string address, unsigned short port);

	void Disconnect();

	int Send(std::vector<char>& buffer, int bufLength);
	int Recv(std::vector<char>& buffer, int bufLength);

	bool IsConnected();
	unsigned short GetPort();
	std::string GetAddress();

private:
	DatagramSocket socket;

	std::string address;
	unsigned short port;
	bool connected;



};

#endif