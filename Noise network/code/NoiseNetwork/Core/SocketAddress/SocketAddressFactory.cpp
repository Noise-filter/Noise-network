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
		return nullptr;
		break;
	}
}

SocketAddress SocketAddressFactory::Create(const std::string ip, const unsigned short port)
{
	addrinfo* addrResult = nullptr;

	int result = getaddrinfo(ip.c_str(), nullptr, nullptr, &addrResult);
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
	return nullptr;
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
		return nullptr;
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
		return nullptr;
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
		return nullptr;
		break;
	}
}

SocketAddress SocketAddressFactory::CreateFromSocket(const SOCKET socket)
{
	if (socket != INVALID_SOCKET)
	{
		socklen_t len;
		struct sockaddr_storage addr;
		char ipstr[INET6_ADDRSTRLEN];
		int port;

		len = sizeof(addr);
		int result = getpeername(socket, (struct sockaddr*)&addr, &len);

		if (result == 0)
		{
			switch (addr.ss_family)
			{
			case AF_INET:
				return (SocketAddress) new SocketAddressIPv4(*(struct sockaddr_in*)&addr);
				break;
			case AF_INET6:
				return (SocketAddress) new SocketAddressIPv6(*(struct sockaddr_in6*)&addr);
				break;
			default:
				return nullptr;
				break;
			}
		}
	}
	return nullptr;
}