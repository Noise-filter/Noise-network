#ifndef SOCKET_ADDRESS_IPV4_H
#define SOCKET_ADDRESS_IPV4_H

#include "SocketAddressInterface.h"

/*
	Inherits from sockaddr_in and works with IPv4 only.
*/
class SocketAddressIPv4 : public SocketAddressInterface, sockaddr_in
{
public:
	SocketAddressIPv4();
	SocketAddressIPv4(const SOCKADDR& addr);
	SocketAddressIPv4(const SOCKADDR_IN& addr);
	SocketAddressIPv4(const std::string ip, const unsigned short port = 0);
	~SocketAddressIPv4();

	std::string GetIP();
	unsigned short GetPort();

	//Returns the ip family being used, either AF_INET or AF_INET6 
	short GetFamily();

	void SetPort(unsigned short port);
	void SetIP(std::string ip);

	const SocketAddressIPv4& operator=(const SOCKADDR& addr);
	const SocketAddressIPv4& operator=(const SOCKADDR_IN& addr);

	operator std::string();
	operator SOCKADDR();
	operator LPSOCKADDR();
	operator LPSOCKADDR_IN();
};

#endif