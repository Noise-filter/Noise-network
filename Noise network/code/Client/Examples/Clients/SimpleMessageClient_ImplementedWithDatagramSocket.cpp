#include "../ClientExamples.h"

#include <iostream>
#include <string>

#include "Core\WinsockFunctions.h"
#include "Core\DatagramSocket.h"

void ClientExamples::SimpleMessageClient_ImplementedWithDatagramSocket(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	DatagramSocket socket;

	if (!socket.Init(AF_INET))
	{
		std::cout << "Error initializing socket" << std::endl;
		return;
	}

	if (!socket.Bind(port+1))
	{
		std::cout << "Error binding" << std::endl;
		return;
	}

	std::string text;
	std::vector<char> buffer;
	sockaddr_in serverAddr;
	hostent* hp = NULL;

	serverAddr.sin_family = AF_INET;
	//TODO: Fix gethostbyname
	//hp = gethostbyname(address.c_str());
	if (hp == NULL)
	{
		std::cout << "Unknown host" << std::endl;
	}

	strcpy_s((char*)&serverAddr.sin_addr, hp->h_length, (char*)hp->h_addr);
	serverAddr.sin_port = htons(port);

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

		result = socket.Send(serverAddr, buffer, (int)text.size());
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		std::cout << "Bytes sent: " << result << std::endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = socket.Recv(serverAddr, buffer, MAX_BUFFER_LENGTH);
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

	socket.Close();

	ShutdownWinSock();
}