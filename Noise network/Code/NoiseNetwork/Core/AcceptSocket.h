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
	bool Init(SocketAddressInterface& bindAddress);
	void Close();

	StreamConnection Accept();

	bool IsInitialized();
	SOCKET GetSocket();

private:
	StreamSocket socket;

};


#endif