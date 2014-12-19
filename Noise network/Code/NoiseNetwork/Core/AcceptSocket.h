#ifndef ACCEPT_SOCKET_H
#define ACCEPT_SOCKET_H

#include "Socket.h"

/*
*	AcceptSocket
*
*	A class whose purpose is to accept tcp connections, nothing more.
*
*
*/
class Socket;
class AcceptSocket
{
public:
	AcceptSocket();
	~AcceptSocket();

	bool Init(unsigned short port);
	void Close();

	SOCKET Accept();

	bool IsInitialized();
	SOCKET GetSocket();

private:
	Socket socket;

};


#endif