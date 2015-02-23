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
	static SocketAddressInterface* Create(const std::string ip, const unsigned short port = 0);
	static SocketAddressInterface* Create(const sockaddr& addr);
	static SocketAddressInterface* Create(const sockaddr_in& addr);
	static SocketAddressInterface* Create(const sockaddr_in6& addr);
};

#endif