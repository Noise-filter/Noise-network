#include "../ClientExamples.h"

#include <iostream>
#include <string>

#include "Core\WinsockFunctions.h"
#include "Core\StreamConnection.h"

void ClientExamples::SimpleMessageClient_ImplementedWithStreamConnection(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	StreamConnection con;

	if (!con.Connect(address, port))
	{
		std::cout << "Error connecting" << std::endl;
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

		result = con.Send(buffer, (int)text.size());
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		std::cout << "Bytes sent: " << result << std::endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = con.Recv(buffer, MAX_BUFFER_LENGTH);
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

	result = con.Disconnect();
	if (result == SOCKET_ERROR)
	{
		std::cout << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
	}

	ShutdownWinSock();
}