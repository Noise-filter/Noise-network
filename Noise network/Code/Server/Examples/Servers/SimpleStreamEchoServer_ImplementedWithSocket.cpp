#include <iostream>

#include "Core\WinsockFunctions.h"
#include "Core\StreamSocket.h"

#include "Core\SocketAddressFactory.h"

const int MAX_BUFFER_LENGTH = 512;

namespace Examples
{
	void SimpleStreamEchoServer_ImplementedWithSocket(unsigned short port)
	{
		if (InitWinSock())
		{
			return;
		}

		std::cout << "Hello World!" << std::endl;

		StreamSocket socket;

		SocketAddress bindAddress = SocketAddressFactory::Create("0.0.0.0", port);

		if (!socket.Init(bindAddress->GetFamily()))
		{
			std::cout << "Error initializing socket" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		if (!socket.Bind(bindAddress))
		{
			std::cout << "Error binding socket" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		if (!socket.Listen())
		{
			std::cout << "Error listening on socket" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		std::cout << "Waiting to accept a client" << std::endl;

		SOCKET clientSocket;
		clientSocket = socket.Accept();
		if (clientSocket == INVALID_SOCKET)
		{
			std::cout << "Error accepting client " << clientSocket << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		std::cout << "Client connected: " << clientSocket << std::endl;

		//No longer need server socket
		socket.Close();

		StreamSocket client(clientSocket);
		std::vector<char> buffer;

		int result = 0;
		do
		{
			buffer.clear();
			buffer.resize(MAX_BUFFER_LENGTH);
			result = client.Recv(buffer, MAX_BUFFER_LENGTH);
			if (result > 0)
			{
				std::cout << "Bytes received: " << result << std::endl;
				std::cout << "Message received: " << &buffer[0] << std::endl;

				result = client.Send(buffer, result);
				if (result == SOCKET_ERROR)
				{
					std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				}
				else
				{
					std::cout << "Bytes send: " << result << std::endl;
				}
			}
			else if (result == 0)
			{
				std::cout << "StreamConnection closing..." << std::endl;
			}
			else
			{
				std::cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
				client.Close();
			}

		} while (result > 0);

		result = client.Shutdown(SD_SEND);
		if (result == SOCKET_ERROR)
		{
			std::cout << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
			client.Close();
		}

		ShutdownWinSock();
	}
}