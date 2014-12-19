#include <iostream>
using namespace std;

namespace
{
	#include "Core\WinsockFunctions.h"
}
#include "Core\AcceptSocket.h"

const int MAX_BUFFER_LENGTH = 512;

namespace Examples
{
	void SimpleEchoServer_ImplementedWithAcceptSocket()
	{
		if (InitWinSock())
		{
			return;
		}

		cout << "Hello World!" << endl;

		AcceptSocket socket;

		//Initialize the AcceptSocket
		//It's that easy
		if (!socket.Init(7878))
		{
			cout << "Error initializing accept socket" << endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		cout << "Waiting to accept a client" << endl;

		SOCKET clientSocket;

		//Wait for a new connection
		clientSocket = socket.Accept();
		if (clientSocket == INVALID_SOCKET)
		{
			cout << "Error accepting client " << clientSocket << endl;
			socket.Close();
			ShutdownWinSock();
			return;
		}

		cout << "Client connected: " << clientSocket << endl;

		//No longer need server socket
		socket.Close();

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
				cout << "Bytes received: " << result << endl;
				cout << "Message received: " << &buffer[0] << endl;

				result = client.Send(buffer, result);
				if (result == SOCKET_ERROR)
				{
					cout << "Send failed with error: " << WSAGetLastError() << endl;
				}
				else
				{
					cout << "Bytes send: " << result << endl;
				}
			}
			else if (result == 0)
			{
				cout << "Connection closing..." << endl;
			}
			else
			{
				cout << "Recv failed with error: " << WSAGetLastError() << endl;
				client.Close();
			}

		} while (result > 0);

		result = client.Shutdown(SD_SEND);
		if (result == SOCKET_ERROR)
		{
			cout << "Shutdown failed with error: " << WSAGetLastError() << endl;
			client.Close();
		}

		ShutdownWinSock();
	}
}