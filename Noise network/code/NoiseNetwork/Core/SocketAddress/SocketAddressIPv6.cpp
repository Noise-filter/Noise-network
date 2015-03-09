#include "SocketAddressIPv6.h"

SocketAddressIPv6::SocketAddressIPv6()
{
	sin6_family = AF_INET6;
	sin6_port = htons(0);
	inet_pton(AF_INET6, "::", &sin6_addr);
}

SocketAddressIPv6::SocketAddressIPv6(const SOCKADDR& addr)
{
	memcpy((SOCKADDR_IN6*)this, (SOCKADDR_IN6*)&addr, sizeof(SOCKADDR_IN6));
}

SocketAddressIPv6::SocketAddressIPv6(const SOCKADDR_IN6& addr)
{
	memcpy((SOCKADDR_IN6*)this, &addr, sizeof(SOCKADDR_IN6));
}

SocketAddressIPv6::SocketAddressIPv6(const std::string ip, const unsigned short port)
{
	sin6_family = AF_INET6;
	sin6_port = htons(port);
	inet_pton(AF_INET6, ip.c_str(), &sin6_addr);
}

SocketAddressIPv6::~SocketAddressIPv6()
{
}

short SocketAddressIPv6::GetFamily()
{
	return sin6_family;
}

std::string SocketAddressIPv6::GetIP()
{
	char str[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &sin6_addr, str, INET6_ADDRSTRLEN);
	return str;
}

unsigned short SocketAddressIPv6::GetPort()
{
	return ntohs(sin6_port);
}

void SocketAddressIPv6::SetPort(unsigned short port)
{
	sin6_port = htons(port);
}

void SocketAddressIPv6::SetIP(std::string ip)
{
	inet_pton(AF_INET6, ip.c_str(), &sin6_addr);
}

const SocketAddressIPv6& SocketAddressIPv6::operator=(const SOCKADDR& addr)
{
	memcpy((SOCKADDR*)this, &addr, sizeof(SOCKADDR));
	return *this;
}

const SocketAddressIPv6& SocketAddressIPv6::operator=(const SOCKADDR_IN6& addr)
{
	memcpy((SOCKADDR_IN6*)this, &addr, sizeof(SOCKADDR_IN6));
	return *this;
}

SocketAddressIPv6::operator std::string()
{
	return GetIP();
}

SocketAddressIPv6::operator SOCKADDR()
{
	return *(LPSOCKADDR)(LPSOCKADDR_IN6)this;
}

SocketAddressIPv6::operator LPSOCKADDR()
{
	return (LPSOCKADDR)(LPSOCKADDR_IN6)this;
}

SocketAddressIPv6::operator LPSOCKADDR_IN6()
{
	return (LPSOCKADDR_IN6)this;
}