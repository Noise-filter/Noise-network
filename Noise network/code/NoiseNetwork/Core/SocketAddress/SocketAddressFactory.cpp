#include "SocketAddressFactory.h"

#include "SocketAddressIPv4.h"
#include "SocketAddressIPv6.h"

SocketAddress SocketAddressFactory::Create(const unsigned short family)
{
	switch (family)
	{
	case AF_INET:
		return (SocketAddress)new SocketAddressIPv4();
		break;
	case AF_INET6:
		return (SocketAddress)new SocketAddressIPv6();
		break;
	default:
		return NULL;
		break;
	}
}

SocketAddress SocketAddressFactory::Create(const std::string ip, const unsigned short port)
{
	addrinfo* addrResult = NULL;

	int result = getaddrinfo(ip.c_str(), NULL, NULL, &addrResult);
	if (result == 0)
	{
		//Check what family the ip address corresponds to
		switch (addrResult->ai_family)
		{
		case AF_INET:
			sockaddr_in sa;
			sa = *(sockaddr_in*)(addrResult->ai_addr);
			sa.sin_port = htons(port);
			return (SocketAddress) new SocketAddressIPv4(sa);
			break;
		case AF_INET6:
			sockaddr_in6 sa6;
			sa6 = *(sockaddr_in6*)(addrResult->ai_addr);
			sa6.sin6_port = htons(port);
			return (SocketAddress) new SocketAddressIPv6(sa6);
			break;
		}
	}

	//Did not match either IPv4 or IPv6
	return NULL;
}

SocketAddress SocketAddressFactory::Create(const sockaddr& addr)
{
	switch (addr.sa_family)
	{
	case AF_INET:
		return (SocketAddress) new SocketAddressIPv4(addr);
		break;
	case AF_INET6:
		return (SocketAddress) new SocketAddressIPv6(addr);
		break;
	default:
		return NULL;
		break;
	}
}

SocketAddress SocketAddressFactory::Create(const sockaddr_in& addr)
{
	switch (addr.sin_family)
	{
	case AF_INET:
		return (SocketAddress) new SocketAddressIPv4(addr);
		break;
	default:
		return NULL;
		break;
	}
}

SocketAddress SocketAddressFactory::Create(const sockaddr_in6& addr)
{
	switch (addr.sin6_family)
	{
	case AF_INET6:
		return (SocketAddress) new SocketAddressIPv6(addr);
		break;
	default:
		return NULL;
		break;
	}
}