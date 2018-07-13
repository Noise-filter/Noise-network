#include "StreamSocket.h"

#include "StreamConnection.h"

StreamSocket::StreamSocket()
{
	socket = INVALID_SOCKET;
	addr = nullptr;
}

StreamSocket::StreamSocket(SOCKET socket)
{
	this->socket = socket;
	addr = SocketAddressFactory::CreateFromSocket(socket);
}

StreamSocket::StreamSocket(SOCKET socket, SocketAddress addr)
{
	this->socket = socket;
	this->addr = addr;
}

StreamSocket::~StreamSocket()
{
}

bool StreamSocket::Init(int family)
{
	socket = ::socket(family, SOCK_STREAM, IPPROTO_TCP);
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

bool StreamSocket::Connect(SocketAddress addr)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = connect(socket, (sockaddr*)*addr, sizeof((sockaddr)*addr));
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	this->addr = addr;

	return true;
}

bool StreamSocket::Bind(SocketAddress addr)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = bind(socket, (sockaddr*)*addr, sizeof((sockaddr)*addr));
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool StreamSocket::Listen()
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = listen(socket, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

StreamConnection StreamSocket::Accept()
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKET clientSocket = INVALID_SOCKET;
	struct sockaddr_storage addr;
	socklen_t addrLen = sizeof(addr);

	clientSocket = accept(socket, (struct sockaddr*)&addr, &addrLen);
	if (clientSocket == INVALID_SOCKET)
	{
		return StreamConnection();
	}

	SocketAddress sockAddr = SocketAddressFactory::Create(*(struct sockaddr*)&addr);

	return StreamConnection(clientSocket, sockAddr);
}

bool StreamSocket::Shutdown(int flag)
{
	if (socket == INVALID_SOCKET)
	{
		return false;
	}

	int result = shutdown(socket, flag);
	if (result == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

void StreamSocket::Close()
{
	closesocket(socket);
	socket = INVALID_SOCKET;
	addr = nullptr;
}

int StreamSocket::Send(std::vector<unsigned char>& buffer, int bufLength)
{
	int result = send(socket, (const char*)&buffer[0], bufLength, 0);
	return result;
}

int StreamSocket::SendAll(std::vector<unsigned char>& buffer, int bufLength)
{
	int size = 0;
	while (size < bufLength) {
		int result = send(socket, (const char*)&buffer[size], bufLength - size, 0);

		if (result > 0) {
			size += result;
		}
		else {
			return result;
		}
	}
	return size;
}

int StreamSocket::SendAll(const BasePackage& package)
{
	auto buffer = package.pack();
	std::vector<unsigned char> sizeBuffer;
	Serializer::Pack(buffer.size(), sizeBuffer);
	buffer.at(0) = sizeBuffer.at(0);
	buffer.at(1) = sizeBuffer.at(1);
	buffer.at(2) = sizeBuffer.at(2);
	buffer.at(3) = sizeBuffer.at(3);
	return SendAll(buffer, buffer.size());
}

int StreamSocket::Recv(std::vector<unsigned char>& buffer, int bufLength)
{
	int result = recv(socket, (char*)&buffer[0], bufLength, 0);
	return result;
}

bool StreamSocket::IsInitialized()
{
	return (socket != INVALID_SOCKET);
}

void StreamSocket::SetSocket(SOCKET socket)
{
	this->socket = socket;
	addr = SocketAddressFactory::CreateFromSocket(socket);
}

SOCKET StreamSocket::GetSocket()
{
	return socket;
}

SocketAddress StreamSocket::GetAddress()
{
	return addr;
}