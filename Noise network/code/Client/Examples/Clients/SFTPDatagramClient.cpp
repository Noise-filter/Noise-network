#include "../ClientExamples.h"

#include <iostream>
#include <string>
#include <fstream>

#include "Core\WinsockFunctions.h"
#include "Core\DatagramConnection.h"

void sftpProtocol(std::string filename, DatagramConnection& socket);

void ClientExamples::SFTPDatagramClient(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	DatagramConnection socket;
	auto serverAddr = SocketAddressFactory::Create(address, port);
	auto bindAddress = SocketAddressFactory::Create("0.0.0.0", 0);
	auto recvAddr = SocketAddressFactory::Create(AF_INET);

	if (!socket.Connect(std::move(serverAddr), *bindAddress))
	{
		std::cout << "Error initializing socket" << std::endl;
		return;
	}

	sftpProtocol("E:/Dropbox/Programming/Github/Noise-network/Noise network/docs/Simple file transfer protocol.pdf", socket);

	socket.Disconnect();

	ShutdownWinSock();
}

void sftpProtocol(std::string filename, DatagramConnection& socket)
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
	std::vector<unsigned char> data;
	data.resize(readSize);
	do
	{
		inFile.read((char*)&data[0], readSize);

		int result = socket.Send(data, (int)inFile.gcount());
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

		result = socket.Recv(data, 1);

		//outFile.write(&data[0], inFile.gcount());
	} while (!inFile.eof());

	inFile.close();
	//outFile.close();
}