#ifndef SOCKET_ADDRESS_IPV6_H
#define SOCKET_ADDRESS_IPV6_H

#include "SocketAddressInterface.h"

/*
	Inherits from sockaddr_in6 and works with IPv6 only.
*/
class SocketAddressIPv6 : public SocketAddressInterface, sockaddr_in6
{
public:
	SocketAddressIPv6();
	SocketAddressIPv6(const SOCKADDR& addr);
	SocketAddressIPv6(const SOCKADDR_IN6& addr);
	SocketAddressIPv6(const std::string& ip, const unsigned short port = 0);

	virtual std::string GetIP() const;
	virtual unsigned short GetPort() const;

	//Returns the ip family being used, either AF_INET or AF_INET6 
	virtual short GetFamily() const;

	virtual void SetPort(unsigned short port);
	virtual void SetIP(const std::string& ip);

	virtual const SocketAddressIPv6& operator=(const SOCKADDR& addr);
	virtual const SocketAddressIPv6& operator=(const SOCKADDR_IN6& addr);

	virtual operator std::string();
	virtual operator SOCKADDR();
	virtual operator LPSOCKADDR();
	virtual operator LPSOCKADDR_IN6();
};

#endif