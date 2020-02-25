#ifndef SOCKET_ADDRESS_INTERFACE_H
#define SOCKET_ADDRESS_INTERFACE_H

#include "..\WinsockIncludes.h"
#include <string>

/*
	This is the interface used for socket address.
	User can implement their own socket address class if they must
	But the provided classes SocketAddressIPv4 and SocketAddressIPv6 should be enough in most cases.

*/
class SocketAddressInterface
{
public:
	//Returns the ip address in decimal dotted or hexadecimal format based on which family is used (IPv4 or IPv6)
	virtual std::string GetIP() const = 0;
	virtual unsigned short GetPort() const = 0;

	//Returns the ip family being used 
	virtual short GetFamily() const = 0;

	//Sets the ip address in decimal dotted or hexadecimal format based on which family is used (IPv4 or IPv6)
	virtual void SetIP(std::string ip) = 0;
	virtual void SetPort(unsigned short port) = 0;

	//Returns the ip address in decimal dotted or hexadecimal format based on which family is used (IPv4 or IPv6)
	virtual operator std::string() = 0;

	virtual operator SOCKADDR() = 0;
	virtual operator LPSOCKADDR() = 0;
};

#endif