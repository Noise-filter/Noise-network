#ifndef CONNECTION_H
#define CONNECTION_H

#include "StreamSocket.h"

class Connection
{
public:
	Connection();
	Connection(SOCKET socket);
	~Connection();

	bool Connect(std::string address, unsigned short port);

	bool Reconnect();
	bool Disconnect();

	int Send(std::vector<char>& buffer, int bufLength);
	int Recv(std::vector<char>& buffer, int bufLength);

	bool IsConnected();
	unsigned short GetPort();
	std::string GetAddress();

private:
	StreamSocket socket;
	
	std::string address;
	unsigned short port;
	bool connected;

};

#endif