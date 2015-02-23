#ifndef CONNECTION_H
#define CONNECTION_H

#include "StreamSocket.h"

class StreamConnection
{
public:
	StreamConnection();
	StreamConnection(SOCKET socket);
	~StreamConnection();

	bool Connect(SocketAddress addr);

	bool Reconnect();
	bool Disconnect();

	int Send(std::vector<char>& buffer, int bufLength);
	int Recv(std::vector<char>& buffer, int bufLength);

	bool IsConnected();
	SocketAddress GetAddress();

private:
	StreamSocket socket;
	
	SocketAddress addr;
	bool connected;

};

#endif