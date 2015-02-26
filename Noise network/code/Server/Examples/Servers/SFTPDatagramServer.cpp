#include <iostream>
#include <fstream>

#include "Core\WinsockFunctions.h"
#include "Core\DatagramSocket.h"

using namespace std;

const int MAX_BUFFER_LENGTH = 1400;

namespace Examples
{
	void SFTPDatagramServer(unsigned short port)
	{
		if (InitWinSock())
		{
			return;
		}

		std::cout << "Hello World!" << std::endl;

		DatagramSocket socket;
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

		std::cout << "Waiting for messages" << std::endl;

		std::vector<char> ackBuffer;
		std::vector<char> buffer;
		SocketAddress from = SocketAddressFactory::Create(AF_INET);

		std::ofstream outFile("C:/Users/Pontus/Downloads/asd.txt", std::ios::binary);
		if (!outFile)
		{
			return;
		}
		std::string a = "A";
		ackBuffer.resize(1);
		ackBuffer.assign(a.begin(), a.end());

		int result = 0;
		do
		{
			buffer.clear();
			buffer.resize(MAX_BUFFER_LENGTH);

			result = socket.Recv(from, buffer, MAX_BUFFER_LENGTH);
			if (result > 0)
			{

				//Parse package and stuff
				outFile.write(&buffer[0], result);

				//std::cout << "\nMessage recieved from: " << from->GetIP() << ":" << from->GetPort() << std::endl;
				//std::cout << "Bytes received: " << result << std::endl;
				//std::cout << "Message received: " << &buffer[0] << std::endl;
				
				result = socket.Send(from, ackBuffer, ackBuffer.size());
				if (result == SOCKET_ERROR)
				{
					std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				}
				else
				{
					//std::cout << "Bytes send: " << result << std::endl;
				}
			}
			else if (result == 0)
			{
				std::cout << "StreamConnection closing..." << std::endl;
			}
			else
			{
				std::cout << "Recv failed with error: " << WSAGetLastError() << std::endl;
				socket.Close();
			}

		} while (result > 0);

		outFile.close();
		socket.Close();
		ShutdownWinSock();
	}
}