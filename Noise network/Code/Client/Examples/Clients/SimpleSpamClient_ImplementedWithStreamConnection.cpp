#include "../ClientExamples.h"

#include <iostream>
#include <string>

#include "Core\WinsockFunctions.h"
#include "Core\StreamConnection.h"

#include "Core\SocketAddress.h"

using namespace std;

void ClientExamples::SimpleSpamClient_ImplementedWithStreamConnection(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	StreamConnection con;

	auto addr = SocketAddressFactory::Create(address, port);

	if (!con.Connect(std::move(addr)))
	{
		std::cout << "Error connecting" << std::endl;
		return;
	}

	const string smallMessage = "Message";
	const string bigMessage = "Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text Big message with more text ";

	//The message which is sent
	std::string message = bigMessage;

	std::vector<unsigned char> buffer;

	int result = 0;
	do
	{
		buffer.clear();
		buffer.assign(message.begin(), message.end());

		result = con.Send(buffer, (int)message.size());
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		//std::cout << "Bytes sent: " << result << std::endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = con.Recv(buffer, MAX_BUFFER_LENGTH);
		if (result > 0)
		{
			//Check if the same message was returned
			std::string returnMessage;
			returnMessage = (char*)buffer.data();

			if (message != returnMessage)
			{
				cout << "=================== ERROR ===================" << endl;
				cout << "The return message was \"" << returnMessage << "\"" << endl;
				cout << "But the sent message was \"" << message << "\"" << endl;

				std::cout << "Bytes received: " << result << std::endl;
				std::cout << "Message received: " << buffer.data() << std::endl;
				cout << "=============================================" << endl;
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

	result = con.Disconnect();
	if (result == SOCKET_ERROR)
	{
		std::cout << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
	}

	ShutdownWinSock();
}