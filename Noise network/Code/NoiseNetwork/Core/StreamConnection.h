#ifndef CONNECTION_H
#define CONNECTION_H

#include "StreamSocket.h"

class StreamConnection
{
public:
	StreamConnection();
	StreamConnection(SOCKET socket);
	StreamConnection(SOCKET socket, std::shared_ptr<SocketAddressInterface> addr);

	bool Connect(std::shared_ptr<SocketAddressInterface> addr);

	bool Reconnect();
	bool Disconnect();

	int Send(std::vector<unsigned char>& buffer, int bufLength);
	int SendAll(std::vector<unsigned char>& buffer, int bufLength);
	int SendAll(const BasePackage& package);

	int Recv(std::vector<unsigned char>& buffer, int bufLength);
	std::unique_ptr<BasePackage> RecvAll();

	bool IsConnected();

	StreamSocket GetSocket();

private:
	StreamSocket socket;

	bool connected;

	std::vector<unsigned char> recvBuffer;

};

#endif