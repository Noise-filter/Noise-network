#ifndef SOCKET_ADDRESS_IPV4_H
#define SOCKET_ADDRESS_IPV4_H

#include "SocketAddressInterface.h"

/*
	Inherits from sockaddr_in and works with IPv4 only.
*/
class SocketAddressIPv4 : public SocketAddressInterface, public sockaddr_in
{
public:
	SocketAddressIPv4();
	SocketAddressIPv4(const SOCKADDR& addr);
	SocketAddressIPv4(const SOCKADDR_IN& addr);
	SocketAddressIPv4(const std::string ip, const unsigned short port = 0);
	virtual ~SocketAddressIPv4();

	virtual std::string GetIP();
	virtual unsigned short GetPort();

	//Returns the ip family being used, either AF_INET or AF_INET6 
	virtual short GetFamily();

	virtual void SetPort(unsigned short port);
	virtual void SetIP(std::string ip);

	virtual const SocketAddressIPv4& operator=(const SOCKADDR& addr);
	virtual const SocketAddressIPv4& operator=(const SOCKADDR_IN& addr);

	virtual operator std::string();
	virtual operator SOCKADDR();
	virtual operator LPSOCKADDR();
	virtual operator LPSOCKADDR_IN();
};

#endif