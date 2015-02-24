#include "../ClientExamples.h"

#include <iostream>
#include <string>

#include "Core\WinsockFunctions.h"
#include "Core\DatagramConnection.h"

void ClientExamples::SimpleSpamClient_ImplementedWithDatagramConnection(std::string address, unsigned short port)
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

	const std::string smallMessage = "Message";
	const std::string bigMessage = "Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text ";

	//The message which is sent
	std::string message = smallMessage;

	std::vector<char> buffer;

	int result = 0;
	do
	{
		buffer.clear();
		buffer.assign(message.begin(), message.end());

		result = socket.Send(buffer, (int)message.size());
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		//std::cout << "Bytes sent: " << result << std::endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = socket.Recv(recvAddr, buffer, MAX_BUFFER_LENGTH);
		if (result > 0)
		{
			//Check if the same message was returned
			std::string returnMessage;
			returnMessage = buffer.data();

			if (message != returnMessage)
			{
				std::cout << "=================== ERROR ===================" << std::endl;
				std::cout << "The return message was \"" << returnMessage << "\"" << std::endl;
				std::cout << "But the sent message was \"" << message << "\"" << std::endl;

				std::cout << "Bytes received: " << result << std::endl;
				std::cout << "Message received: " << buffer.data() << std::endl;
				std::cout << "=============================================" << std::endl;
			}
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

	} while (message.size() > 0);

	socket.Disconnect();

	ShutdownWinSock();
}