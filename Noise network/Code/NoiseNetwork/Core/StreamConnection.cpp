#include "StreamConnection.h"

#include "Package\PackageFactory.h"
#include "WinsockFunctions.h"

StreamConnection::StreamConnection()
{
	connected = false;
}

StreamConnection::StreamConnection(SOCKET socket)
{
	this->socket = StreamSocket(socket);
	if (socket != INVALID_SOCKET)
	{
		connected = true;
	}
	else
	{
		connected = false;
	}
}

StreamConnection::StreamConnection(SOCKET socket, std::shared_ptr<SocketAddressInterface> addr)
{
	this->socket = StreamSocket(socket, addr);
	if (socket != INVALID_SOCKET)
	{
		connected = true;
	}
	else
	{
		connected = false;
	}
}

bool StreamConnection::Connect(std::shared_ptr<SocketAddressInterface> addr)
{
	recvBuffer.clear();
	//Try to initialize socket if it isn't already initialized
	if (!socket.IsInitialized())
	{
		if (!socket.Init(addr->GetFamily()))
		{
			return false;
		}
	}

	//Try to connect
	bool result = socket.Connect(addr);

	connected = result;

	return connected;
}

bool StreamConnection::Reconnect()
{
	//Return true if already connected
	if (connected)
	{
		return true;
	}

	//Only try to reconnect if connect has already been called 
	if (socket.GetAddress())
	{
		recvBuffer.clear();
		return Connect(socket.GetAddress());
	}
	
	return false;
}

bool StreamConnection::Disconnect()
{
	if (connected)
	{
		socket.Shutdown(SD_SEND);
		socket.Close();
		connected = false;
		recvBuffer.clear();
	}

	return true;
}

int StreamConnection::Send(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Send(buffer, bufLength);
	}

	return 0;
}

int StreamConnection::SendAll(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.SendAll(buffer, bufLength);
	}

	return 0;
}

int StreamConnection::SendAll(const BasePackage& package)
{
	if (connected)
	{
		auto buffer = package.pack();
		std::vector<unsigned char> sizeBuffer;
		Serializer::Pack((unsigned int)buffer.size(), sizeBuffer);
		buffer.at(0) = sizeBuffer.at(0);
		buffer.at(1) = sizeBuffer.at(1);
		buffer.at(2) = sizeBuffer.at(2);
		buffer.at(3) = sizeBuffer.at(3);
		return SendAll(buffer, (int)buffer.size());
	}

	return 0;
}

int StreamConnection::Recv(std::vector<unsigned char>& buffer, int bufLength)
{
	if (connected)
	{
		return socket.Recv(buffer, bufLength);
	}

	return 0;
}

std::unique_ptr<BasePackage> StreamConnection::RecvAll()
{
	if (connected)
	{
		// Check recvBuffer for package first
		while (true) {
			if (recvBuffer.size() >= 4) {
				unsigned int size = 0;
				unsigned int index = Serializer::Unpack(recvBuffer, 0, size);

				if (size != 0 && size <= recvBuffer.size()) {
					// Unpack a package from recvBuffer
					std::vector<unsigned char> msgBuffer = { begin(recvBuffer), begin(recvBuffer) + size };
					recvBuffer.erase(begin(recvBuffer), begin(recvBuffer) + size);
					//recvBuffer = {begin(recvBuffer) + size, end(recvBuffer)};
					int id;
					index = Serializer::Unpack(msgBuffer, index, id);

					//Get correct package type based on id
					auto package = PackageFactory::getInstance().create(id);

					//Call unpack and return the Package
					index = 0;
					package->unpack(msgBuffer, index);
					return package;
				}
			}

			std::vector<unsigned char> buffer(512);
			int result = Recv(buffer, 512);

			if (result > 0) {
				recvBuffer.insert(end(recvBuffer), begin(buffer), begin(buffer) + result);
			}
			else {
				return std::make_unique<ErrorPackage>();
			}
		}
	}
	return std::make_unique<ErrorPackage>(PackageErrors::NOT_CONNECTED);
}

bool StreamConnection::IsConnected()
{
	return connected;
}

StreamSocket StreamConnection::GetSocket()
{
	return socket;
}