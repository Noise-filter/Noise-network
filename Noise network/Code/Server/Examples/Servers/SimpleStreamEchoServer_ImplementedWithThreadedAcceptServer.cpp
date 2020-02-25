#include <iostream>

#include "Core\WinsockFunctions.h"
#include "Core\ThreadedAcceptServer.h"

#include "Core\SocketAddress.h"

using namespace std;

const int MAX_BUFFER_LENGTH = 512;

namespace Examples
{
	void SimpleStreamEchoServer_ImplementedWithThreadedAcceptServer(unsigned short port)
	{
		if (InitWinSock())
		{
			return;
		}

		cout << "Hello World!" << std::endl;

		ThreadedAcceptServer acceptServer;

		auto bindAddress = SocketAddressFactory::Create("0.0.0.0", port);

		//Initialize the AcceptSocket
		//It's that easy
		if (!acceptServer.Init(*bindAddress))
		{
			cout << "Error initializing accept socket" << std::endl;
			acceptServer.Stop();
			ShutdownWinSock();
			return;
		}

		//Start accept thread
		acceptServer.Start();

		cout << "Waiting to accept a client" << std::endl;

		StreamConnection client;

		//Wait for connection
		do
		{
			if (acceptServer.WaitingClients())
			{
				client = acceptServer.GetConnectedClient();
				cout << "Client connected: " << client.GetSocket().GetSocket() << std::endl;
			}

		} while (!client.IsConnected());

		//No longer need server socket
		//Stop the accept thread
		acceptServer.Stop();

		std::vector<unsigned char> buffer;

		int result = 0;
		do
		{
			buffer.clear();
			buffer.resize(MAX_BUFFER_LENGTH);
			result = client.Recv(buffer, MAX_BUFFER_LENGTH);
			if (result > 0)
			{
				//cout << "Bytes received: " << result << std::endl;
				//cout << "Message received: " << &buffer[0] << std::endl;

				result = client.Send(buffer, result);
				if (result == SOCKET_ERROR)
				{
					cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				}
				else
				{
					//cout << "Bytes send: " << result << std::endl;
				}
			}
			else if (result == 0)
			{
				cout << "Connection closing..." << std::endl;
			}
			else
			{
				cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
				client.Disconnect();
			}

		} while (result > 0);

		result = client.Disconnect();

		ShutdownWinSock();
	}
}