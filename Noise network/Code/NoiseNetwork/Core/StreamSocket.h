#ifndef SOCKET_H
#define SOCKET_H

#include "WinsockIncludes.h"
#include <vector>
#include <memory>

#include "SocketAddress.h"
#include "Package\BasePackage.h"

class StreamConnection;

class StreamSocket
{
public:
	StreamSocket();
	StreamSocket(SOCKET socket);
	StreamSocket(SOCKET socket, const std::shared_ptr<SocketAddressInterface>& addr);

	//Creates a SOCKET
	bool Init(int family);

	bool Connect(const std::shared_ptr<SocketAddressInterface>& addr);

	bool Bind(SocketAddressInterface& addr);
	bool Listen();
	StreamConnection Accept();

	//Shutdown socket with SD_RECEIVE, SD_SEND or SD_BOTH
	//This will turn off receive, send or both for the socket
	//Does not close the socket, Close has to be called separately
	bool Shutdown(int flag);

	//Closes the socket
	void Close();

	//Will note clear or resize the buffer
	int Send(std::vector<unsigned char>& buffer, int bufLength);

	//Will send until everything in the buffer is sent
	int SendAll(std::vector<unsigned char>& buffer, int bufLength);

	//Will not clear or resize the buffer
	int Recv(std::vector<unsigned char>& buffer, int bufLength);

	//Returns true if SOCKET is not an INVALID_SOCKET
	bool IsInitialized();

	void SetSocket(SOCKET socket);

	SOCKET GetSocket();
	std::shared_ptr<SocketAddressInterface> GetAddress();

private:
	SOCKET socket;
	std::shared_ptr<SocketAddressInterface> addr;

};

#endif // !SOCKET_H