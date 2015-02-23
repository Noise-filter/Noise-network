#include "SocketAddressFactory.h"

#include "SocketAddressIPv4.h"
#include "SocketAddressIPv6.h"

SocketAddressInterface* SocketAddressFactory::Create(const std::string ip, const unsigned short port)
{
	//Check if it is an IPv4 address
	sockaddr_in sa;
	int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
	if (result == 1)
	{
		sa.sin_family = AF_INET;
		sa.sin_port = htons(port);
		return new SocketAddressIPv4(sa);
	}

	//Check if it is an IPv6 address
	sockaddr_in6 sa6;
	result = inet_pton(AF_INET6, ip.c_str(), &(sa6.sin6_addr));
	if (result == 1)
	{
		sa6.sin6_family = AF_INET6;
		sa6.sin6_port = htons(port);
		return new SocketAddressIPv6(sa6);
	}

	//Did not match either IPv4 or IPv6
	return NULL;
}

SocketAddressInterface* SocketAddressFactory::Create(const sockaddr& addr)
{
	switch (addr.sa_family)
	{
	case AF_INET:
		return new SocketAddressIPv4(addr);
		break;
	case AF_INET6:
		return new SocketAddressIPv6(addr);
		break;
	default:
		return NULL;
		break;
	}
	return NULL;
}

SocketAddressInterface* SocketAddressFactory::Create(const sockaddr_in& addr)
{
	switch (addr.sin_family)
	{
	case AF_INET:
		return new SocketAddressIPv4(addr);
		break;
	case AF_INET6:
		return new SocketAddressIPv6((const sockaddr_in6&)addr);
		break;
	default:
		return NULL;
		break;
	}
	return NULL;
}

SocketAddressInterface* SocketAddressFactory::Create(const sockaddr_in6& addr)
{
	switch (addr.sin6_family)
	{
	case AF_INET6:
		return new SocketAddressIPv6(addr);
		break;
	default:
		return NULL;
		break;
	}
	return NULL;
}