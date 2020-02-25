#include <iostream>

#include "Core\WinsockFunctions.h"
#include "Core\AcceptSocket.h"
#include "Core\StreamConnection.h"

#include "Core\SocketAddress.h"

const int MAX_BUFFER_LENGTH = 512;

namespace Examples
{
	void SimpleStreamEchoServer_ImplementedWithAcceptSocket(unsigned short port)
	{
		if (InitWinSock())
		{
			return;
		}

		std::cout << "Hello World!" << std::endl;

		AcceptSocket socket;

		auto bindAddress = SocketAddressFactory::Create("0.0.0.0", port);

		//Initialize the AcceptSocket
		//It's that easy
		if (!socket.Init(*bindAddress))
		{
			std::cout << "Error initializing accept socket" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		std::cout << "Waiting to accept a client" << std::endl;

		//Wait for a new connection
		StreamConnection client = socket.Accept();
		if (!client.IsConnected())
		{
			std::cout << "Error accepting client" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		std::cout << "Client connected: " << client.GetSocket().GetSocket() << std::endl;

		//No longer need server socket
		socket.Close();

		std::vector<unsigned char> buffer;

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
				std::cout << "Connection closing..." << std::endl;
			}
			else
			{
				std::cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
				client.Disconnect();
			}

		} while (result > 0);

		result = client.Disconnect();

		ShutdownWinSock();
	}
}