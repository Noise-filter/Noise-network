#ifndef SOCKET_H
#define SOCKET_H

#include "WinsockIncludes.h"
#include <vector>

class Socket
{
public:
	Socket();
	Socket(SOCKET socket);
	virtual ~Socket();

	//Creates a SOCKET
	bool Init(int family, int type, int protocol);

	bool Connect(std::string address, unsigned short port);

	bool Bind(unsigned short port);
	bool Listen();
	SOCKET Accept();

	//Shutdown socket with SD_RECEIVE, SD_SEND or SD_BOTH
	//This will turn off receive, send or both for the socket
	//Does not close the socket, Close has to be called separately
	bool Shutdown(int flag);

	//Closes the socket
	void Close();

	//Will 
	int Send(std::vector<char>& buffer, int bufLength);

	//Will not clear or resize the buffer
	int Recv(std::vector<char>& buffer, int bufLength);

	//Returns true if SOCKET is not an INVALID_SOCKET
	bool IsInitialized();

	void SetSocket(SOCKET socket);
	SOCKET GetSocket();

private:
	SOCKET socket;
	struct sockaddr_in server;

};

#endif // !SOCKET_H