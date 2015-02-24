#include "../ClientExamples.h"

#include <iostream>
#include <string>

#include "Core\WinsockFunctions.h"
#include "Core\DatagramConnection.h"

void ClientExamples::SimpleMessageClient_ImplementedWithDatagramConnection(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	DatagramConnection socket;
	SocketAddress serverAddr = SocketAddressFactory::Create(address, port);
	SocketAddress bindAddress = SocketAddressFactory::Create("0.0.0.0", port + 1);
	SocketAddress recvAddr = SocketAddressFactory::Create(AF_INET);

	if (!socket.Connect(serverAddr, bindAddress))
	{
		std::cout << "Error initializing socket" << std::endl;
		return;
	}

	std::string text;
	std::vector<char> buffer;

	int result = 0;
	do
	{
		std::cout << "> ";
		getline(std::cin, text);

		if (text.size() == 0)
		{
			break;
		}

		buffer.clear();
		buffer.assign(text.begin(), text.end());

		result = socket.Send(buffer, (int)text.size());
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		std::cout << "Bytes sent: " << result << std::endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = socket.Recv(recvAddr, buffer, MAX_BUFFER_LENGTH);
		if (result > 0)
		{
			std::cout << "Bytes received: " << result << std::endl;
			std::cout << "Message received: " << buffer.data() << std::endl;
		}
		else if (result == 0)
		{
			std::cout << "Connection closed" << std::endl;
			return;
		}
		else
		{
			std::cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
			return;
		}

	} while (text.size() > 0);

	socket.Disconnect();

	ShutdownWinSock();
}