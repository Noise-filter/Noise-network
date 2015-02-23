#ifndef ACCEPT_SOCKET_H
#define ACCEPT_SOCKET_H

#include "StreamSocket.h"

/*
*	AcceptSocket
*
*	A class whose purpose is to accept tcp connections, nothing more.
*
*
*/
class StreamSocket;
class AcceptSocket
{
public:
	AcceptSocket();
	~AcceptSocket();

	bool Init(SocketAddress bindAddress);
	void Close();

	SOCKET Accept();

	bool IsInitialized();
	SOCKET GetSocket();

private:
	StreamSocket socket;

};


#endif