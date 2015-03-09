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
	virtual ~SocketAddressInterface() {}

	//Returns the ip address in decimal dotted or hexadecimal format based on which family is used (IPv4 or IPv6)
	virtual std::string GetIP() = 0;
	virtual unsigned short GetPort() = 0;

	//Returns the ip family being used 
	virtual short GetFamily() = 0;

	//Sets the ip address in decimal dotted or hexadecimal format based on which family is used (IPv4 or IPv6)
	virtual void SetIP(std::string ip) = 0;
	virtual void SetPort(unsigned short port) = 0;

	//Returns the ip address in decimal dotted or hexadecimal format based on which family is used (IPv4 or IPv6)
	virtual operator std::string() = 0;

	virtual operator SOCKADDR() = 0;
	virtual operator LPSOCKADDR() = 0;
};

//memory include for std::shared_ptr
#include <memory>

typedef std::shared_ptr<SocketAddressInterface> SocketAddress;

#endif