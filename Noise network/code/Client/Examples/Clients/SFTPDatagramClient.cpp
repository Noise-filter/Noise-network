#include "../ClientExamples.h"

#include <iostream>
#include <string>
#include <fstream>

#include "Core\WinsockFunctions.h"
#include "Core\DatagramConnection.h"

void sftpProtocol(std::string filename, DatagramConnection socket);

void ClientExamples::SFTPDatagramClient(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	DatagramConnection socket;
	SocketAddress serverAddr = SocketAddressFactory::Create(address, port);
	SocketAddress bindAddress = SocketAddressFactory::Create("0.0.0.0", port + 1);
	SocketAddress recvAddr = SocketAddressFactory::Create(AF_INET);


	if (!socket.Connect(serverAddr, bindAddress))
	{
		std::cout << "Error initializing socket" << std::endl;
		return;
	}

	sftpProtocol("E:/Visual Studio 2013 Professional 32-bit (English)/en_vs2013_rtm_pro_enu.iso", socket);

	std::string text;
	std::vector<char> buffer;

	int result = 0;
	do
	{
		/*std::cout << "> ";
		getline(std::cin, text);

		if (text.size() == 0)
		{
			break;
		}

		buffer.clear();
		buffer.assign(text.begin(), text.end());

		result = socket.Send(buffer, (int)text.size());
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		std::cout << "Bytes sent: " << result << std::endl;

		buffer.clear();
		buffer.resize(MAX_BUFFER_LENGTH);

		result = socket.Recv(recvAddr, buffer, MAX_BUFFER_LENGTH);
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
		}*/

	} while (text.size() > 0);

	socket.Disconnect();

	ShutdownWinSock();
}

void sftpProtocol(std::string filename, DatagramConnection socket)
{
	std::ifstream inFile(filename, std::ios::binary);
	if (!inFile)
	{
		return;
	}
	/*
	std::ofstream outFile(filename + ".out", std::ios::binary);
	if (!outFile)
	{
		inFile.close();
		return;
	}*/

	int totalSent = 0;
	int readSize = 1400;
	std::vector<char> data;
	data.resize(readSize);
	SocketAddress addr = SocketAddressFactory::Create(AF_INET);
	do
	{
		inFile.read(&data[0], readSize);

		int result = socket.Send(data, inFile.gcount());
		if (result == -1)
		{
			std::cout << "ERROR" << std::endl;
			break;//ERROR
		}
		else if (result < inFile.gcount())
		{
			std::cout << "Sent only: " << inFile.gcount() << " bytes" << std::endl;
			break;
		}
		
		if (result != inFile.gcount())
		{
			std::cout << result << std::endl;
		}
		totalSent += result;
		//std::cout << "Sent: " << result << std::endl;
		//std::cout << "Total: " << totalSent << std::endl;

		result = socket.Recv(addr, data, 1);

		//outFile.write(&data[0], inFile.gcount());
	} while (!inFile.eof());

	inFile.close();
	//outFile.close();
}