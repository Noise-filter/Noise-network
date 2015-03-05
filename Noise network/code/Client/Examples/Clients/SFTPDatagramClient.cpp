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
	SocketAddress bindAddress = SocketAddressFactory::Create("0.0.0.0", 0);
	SocketAddress recvAddr = SocketAddressFactory::Create(AF_INET);


	if (!socket.Connect(serverAddr, bindAddress))
	{
		std::cout << "Error initializing socket" << std::endl;
		return;
	}

	sftpProtocol("E:/Dropbox/Programming/Github/Noise-network/Noise network/docs/Simple file transfer protocol.pdf", socket);

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