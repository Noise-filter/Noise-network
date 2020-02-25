#ifndef SOCKET_ADDRESS_FACTORY_H
#define SOCKET_ADDRESS_FACTORY_H

#include "SocketAddressInterface.h"
#include <memory>

/*
	This is the best way to create a SocketAddress object
	This factory should create the correct SocketAddress class, either IPv4 or IPv6
*/
class SocketAddressFactory
{
public:
	//Creates a empty SocketAddress of the family parameter.
	//Supports AF_INET and AF_INET6
	static auto Create(const unsigned short family) -> std::unique_ptr<SocketAddressInterface>;
	static auto Create(const std::string ip, const unsigned short port = 0) -> std::unique_ptr<SocketAddressInterface>;
	static auto Create(const sockaddr& addr) -> std::unique_ptr<SocketAddressInterface>;
	static auto Create(const sockaddr_in& addr) -> std::unique_ptr<SocketAddressInterface>;
	static auto Create(const sockaddr_in6& addr) -> std::unique_ptr<SocketAddressInterface>;
	static auto CreateFromSocket(const SOCKET socket) -> std::unique_ptr<SocketAddressInterface>;
};

#endif