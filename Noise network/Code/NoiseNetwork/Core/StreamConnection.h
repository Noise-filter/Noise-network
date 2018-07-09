#ifndef CONNECTION_H
#define CONNECTION_H

#include "StreamSocket.h"

class StreamConnection
{
public:
	StreamConnection();
	StreamConnection(SOCKET socket);
	StreamConnection(SOCKET socket, SocketAddress addr);
	~StreamConnection();

	bool Connect(SocketAddress addr);

	bool Reconnect();
	bool Disconnect();

	int Send(std::vector<unsigned char>& buffer, int bufLength);
	int SendAll(std::vector<unsigned char>& buffer, int bufLength);

	int Recv(std::vector<unsigned char>& buffer, int bufLength);

	bool IsConnected();

	StreamSocket GetSocket();

private:
	StreamSocket socket;

	bool connected;

};

#endif