#include "SocketAddressFactory.h"

#include "SocketAddressIPv4.h"
#include "SocketAddressIPv6.h"

auto SocketAddressFactory::Create(const unsigned short family) -> std::unique_ptr<SocketAddressInterface>
{
	switch (family)
	{
	case AF_INET:
		return std::make_unique<SocketAddressIPv4>();
	case AF_INET6:
		return std::make_unique<SocketAddressIPv6>();
	default:
		return nullptr;
	}
}

auto SocketAddressFactory::Create(const std::string& ip, const unsigned short port) -> std::unique_ptr<SocketAddressInterface>
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
			return std::make_unique<SocketAddressIPv4>(sa);
		case AF_INET6:
			sockaddr_in6 sa6;
			sa6 = *(sockaddr_in6*)(addrResult->ai_addr);
			sa6.sin6_port = htons(port);
			return std::make_unique<SocketAddressIPv6>(sa6);
		}
	}

	//Did not match either IPv4 or IPv6
	return nullptr;
}

auto SocketAddressFactory::Create(const sockaddr& addr) -> std::unique_ptr<SocketAddressInterface>
{
	switch (addr.sa_family)
	{
	case AF_INET:
		return std::make_unique<SocketAddressIPv4>(addr);
	case AF_INET6:
		return std::make_unique<SocketAddressIPv6>(addr);
	default:
		return nullptr;
	}
}

auto SocketAddressFactory::Create(const sockaddr_in& addr) -> std::unique_ptr<SocketAddressInterface>
{
	switch (addr.sin_family)
	{
	case AF_INET:
		return std::make_unique<SocketAddressIPv4>(addr);
	default:
		return nullptr;
	}
}

auto SocketAddressFactory::Create(const sockaddr_in6& addr) -> std::unique_ptr<SocketAddressInterface>
{
	switch (addr.sin6_family)
	{
	case AF_INET6:
		return std::make_unique<SocketAddressIPv6>(addr);
	default:
		return nullptr;
	}
}

auto SocketAddressFactory::CreateFromSocket(const SOCKET socket) -> std::unique_ptr<SocketAddressInterface>
{
	if (socket != INVALID_SOCKET)
	{
		socklen_t len;
		struct sockaddr_storage addr;

		len = sizeof(addr);
		int result = getpeername(socket, (struct sockaddr*)&addr, &len);

		if (result == 0)
		{
			switch (addr.ss_family)
			{
			case AF_INET:
				return std::make_unique<SocketAddressIPv4>(*(struct sockaddr_in*)&addr);
			case AF_INET6:
				return std::make_unique<SocketAddressIPv6>(*(struct sockaddr_in6*)&addr);
			default:
				return nullptr;
			}
		}
	}
	return nullptr;
}