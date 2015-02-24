#ifndef SOCKET_ADDRESS_FACTORY_H
#define SOCKET_ADDRESS_FACTORY_H

#include "SocketAddressInterface.h"

/*
	This is the best way to create a SocketAddress object
	This factory should create the correct SocketAddress class, either IPv4 or IPv6
*/
class SocketAddressFactory
{
public:
	//Creates a empty SocketAddress of the family parameter.
	//Supports AF_INET and AF_INET6
	static SocketAddress Create(const unsigned short family);
	static SocketAddress Create(const std::string ip, const unsigned short port = 0);
	static SocketAddress Create(const sockaddr& addr);
	static SocketAddress Create(const sockaddr_in& addr);
	static SocketAddress Create(const sockaddr_in6& addr);
};

#endif