#include "SocketAddressIPv4.h"

SocketAddressIPv4::SocketAddressIPv4()
{
	sin_family = AF_INET;
	sin_port = htons(0);
	inet_pton(AF_INET, "0.0.0.0", &sin_addr);
}

SocketAddressIPv4::SocketAddressIPv4(const SOCKADDR& addr)
{ 
	memcpy((SOCKADDR_IN*)this, (SOCKADDR_IN*)&addr, sizeof(SOCKADDR_IN));
}

SocketAddressIPv4::SocketAddressIPv4(const SOCKADDR_IN& addr)
{
	memcpy((SOCKADDR_IN*)this, &addr, sizeof(SOCKADDR_IN)); 
}

SocketAddressIPv4::SocketAddressIPv4(const std::string ip, const unsigned short port)
{
	sin_family = AF_INET;
	sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &sin_addr);
}

SocketAddressIPv4::~SocketAddressIPv4()
{
}

short SocketAddressIPv4::GetFamily()
{
	return sin_family;
}

std::string SocketAddressIPv4::GetIP()
{
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &sin_addr, str, INET_ADDRSTRLEN);
	return str;
}

unsigned short SocketAddressIPv4::GetPort()
{
	return ntohs(sin_port);
}

void SocketAddressIPv4::SetPort(unsigned short port)
{
	sin_port = htons(port);
}

void SocketAddressIPv4::SetIP(std::string ip)
{
	inet_pton(AF_INET, ip.c_str(), &sin_addr);
}

const SocketAddressIPv4& SocketAddressIPv4::operator=(const SOCKADDR& addr)
{
	memcpy((SOCKADDR_IN*)this, (SOCKADDR_IN*)&addr, sizeof(SOCKADDR_IN));
	return *this;
}
const SocketAddressIPv4& SocketAddressIPv4::operator=(const SOCKADDR_IN& addr)
{
	memcpy((SOCKADDR_IN*)this, &addr, sizeof(SOCKADDR_IN));
	return *this;
}

SocketAddressIPv4::operator std::string()
{
	return GetIP();
}

SocketAddressIPv4::operator SOCKADDR()
{
	return *(LPSOCKADDR)(LPSOCKADDR_IN)this;
}

SocketAddressIPv4::operator LPSOCKADDR()
{
	return (LPSOCKADDR)(LPSOCKADDR_IN)this;
}

SocketAddressIPv4::operator LPSOCKADDR_IN()
{
	return (LPSOCKADDR_IN)this;
}