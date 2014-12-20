#include <iostream>

#include "Core\WinsockFunctions.h"
#include "Core\ThreadedAcceptServer.h"

using namespace std;

const int MAX_BUFFER_LENGTH = 512;

namespace Examples
{
	void SimpleEchoServer_ImplementedWithThreadedAcceptServer()
	{
		if (InitWinSock())
		{
			return;
		}

		cout << "Hello World!" << std::endl;

		ThreadedAcceptServer acceptServer;

		//Initialize the AcceptSocket
		//It's that easy
		if (!acceptServer.Init(7878))
		{
			cout << "Error initializing accept socket" << std::endl;
			acceptServer.Stop();
			ShutdownWinSock();
			return;
		}

		//Start accept thread
		acceptServer.Start();

		cout << "Waiting to accept a client" << std::endl;


		SOCKET clientSocket = INVALID_SOCKET;
		
		//Wait for connection
		do
		{
			if (acceptServer.WaitingClients())
			{
				clientSocket = acceptServer.GetConnectedClient();
				cout << "Client connected: " << clientSocket << std::endl;
			}

		} while (clientSocket == INVALID_SOCKET);

		//No longer need server socket
		//Stop the accept thread
		acceptServer.Stop();

		Socket client(clientSocket);
		std::vector<char> buffer;

		int result = 0;
		do
		{
			buffer.clear();
			buffer.resize(MAX_BUFFER_LENGTH);
			result = client.Recv(buffer, MAX_BUFFER_LENGTH);
			if (result > 0)
			{
				cout << "Bytes received: " << result << std::endl;
				cout << "Message received: " << &buffer[0] << std::endl;

				result = client.Send(buffer, result);
				if (result == SOCKET_ERROR)
				{
					cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				}
				else
				{
					cout << "Bytes send: " << result << std::endl;
				}
			}
			else if (result == 0)
			{
				cout << "Connection closing..." << std::endl;
			}
			else
			{
				cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
				client.Close();
			}

		} while (result > 0);

		result = client.Shutdown(SD_SEND);
		if (result == SOCKET_ERROR)
		{
			cout << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
			client.Close();
		}

		ShutdownWinSock();
	}
}