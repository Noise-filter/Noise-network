#include <iostream>

#include "Core\WinsockFunctions.h"
#include "Core\StreamSocket.h"
#include "Core\StreamConnection.h"

#include "Core\SocketAddress.h"

const int MAX_BUFFER_LENGTH = 512;

#include "../Client/Examples/Clients/PackableClass.h"
#include "Core\Package\PackageFactory.h"

namespace Examples
{
	void SimpleStreamEchoServer_ImplementedWithSocket(unsigned short port)
	{
		if (InitWinSock())
		{
			return;
		}

		std::cout << "Hello World!" << std::endl;
		
		PackageFactory::getInstance().registerPackage(0, []() { return std::make_unique<PackableClass>(); });

		auto bindAddress = SocketAddressFactory::Create("0.0.0.0", port);
		StreamSocket socket;
		if (!socket.Init(bindAddress->GetFamily()))
		{
			std::cout << "Error initializing socket" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		if (!socket.Bind(*bindAddress))
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

		StreamConnection client;
		client = socket.Accept();
		if (!client.IsConnected())
		{
			std::cout << "Error accepting client" << std::endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}
		//No longer need server socket
		socket.Close();

		std::cout << "Client connected: " << client.GetSocket().GetSocket() << std::endl;

		int result = 0;
		do
		{
			auto package = client.RecvAll();
			if (package->getId() >= 0)
			{
				//std::cout << "Bytes received: " << result << std::endl;

				//auto person = dynamic_cast<PackableClass*>(package.get());
				//person->print();

				result = client.SendAll(*package.get());
				if (result == SOCKET_ERROR)
				{
					std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				}
				else
				{
					//std::cout << "Bytes send: " << result << std::endl;
				}
			}
			else
			{
				auto errorPackage = dynamic_cast<ErrorPackage*>(package.get());
				std::cout << "Recv failed with error: " << static_cast<typename std::underlying_type<PackageErrors>::type>(errorPackage->getErrorCode()) << std::endl;
				std::cout << "StreamConnection closing..." << std::endl;
				client.Disconnect();
			}

		} while (result > 0);

		client.Disconnect();
		ShutdownWinSock();
	}
}