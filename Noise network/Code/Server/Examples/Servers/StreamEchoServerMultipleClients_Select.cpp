#include <iostream>

#include "Core\WinsockFunctions.h"
#include "Core\ThreadedAcceptServer.h"

#include "Core\SocketAddress.h"

using namespace std;

const int MAX_BUFFER_LENGTH = 3000;

namespace Examples
{
	void StreamEchoServerMultipleClients_Select(unsigned short port)
	{
		if (InitWinSock())
		{
			return;
		}

		cout << "Hello World! Michelle �r b�st" << std::endl;

		ThreadedAcceptServer acceptServer;

		auto bindAddress = SocketAddressFactory::Create("0.0.0.0", port);

		//Initialize the AcceptSocket
		if (!acceptServer.Init(*bindAddress))
		{
			cout << "Error initializing accept socket" << std::endl;
			acceptServer.Stop();
			ShutdownWinSock();
			return;
		}

		//Start accept thread
		acceptServer.Start();
		cout << "Accept thread started" << endl;

		SOCKET clientSocket = INVALID_SOCKET;
		vector<StreamSocket> clients;

		vector<unsigned char> buffer;

		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 500;

		FD_SET readSet;
		FD_SET masterSet;

		FD_ZERO(&masterSet);

		int clientCounter = 0;

		int result = 0;
		do
		{
			readSet = masterSet;

			if (readSet.fd_count > 0)
			{
				result = select(0, &readSet, NULL, NULL, &timeout);
				if (result == SOCKET_ERROR)
				{
					cout << "Select failed with error: " << WSAGetLastError() << endl;
				}
			}

			for (unsigned int i = 0; i < readSet.fd_count; i++)
			{
				clientSocket = readSet.fd_array[i];

				vector<unsigned char> buffer(MAX_BUFFER_LENGTH);

				result = recv(clientSocket, (char*)&buffer[0], MAX_BUFFER_LENGTH, 0);
				if (result > 0)
				{
					//cout << "Bytes: " << result;
					//cout << " Client: " << clientSocket << " Message: " << &buffer[0] << std::endl;

					result = send(clientSocket, (const char*)&buffer[0], result, 0);
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
					FD_CLR(clientSocket, &masterSet);
					closesocket(clientSocket);
					clientSocket = INVALID_SOCKET;
					clientCounter--;
				}
				else
				{
					cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
					FD_CLR(clientSocket, &masterSet);
					closesocket(clientSocket);
					clientSocket = INVALID_SOCKET;
					clientCounter--;
				}
			}

			//Accept new clients
			if (acceptServer.WaitingClients())
			{
				//TODO: This must be fixed. Write my own select server maybe?
				clientSocket = acceptServer.GetConnectedClient().GetSocket().GetSocket();
				FD_SET(clientSocket, &masterSet);
				clientCounter++;
				cout << "Client connected: " << clientSocket << ' ' << clientCounter << std::endl;
			}

		} while (true);

		//Stop the accept thread
		acceptServer.Stop();

		ShutdownWinSock();
	}
}