#include "../ClientExamples.h"

#include <iostream>
#include <string>

#include "Core\WinsockFunctions.h"
#include "Core\StreamConnection.h"

#include "Core\SocketAddress.h"
#include "Core\Package\PackageFactory.h"

#include "PackableClass.h"

void ClientExamples::SimpleMessageClient_ImplementedWithStreamConnection(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	PackageFactory::getInstance().registerPackage(0, []() { return new PackableClass; });

	SocketAddress addr = SocketAddressFactory::Create(address, port);
	StreamConnection con;
	if (!con.Connect(addr))
	{
		std::cout << "Error connecting" << std::endl;
		return;
	}

	int result = 0;
	do
	{
		PackableClass person;
		result = con.SendAll(person);
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		std::cout << "Bytes sent: " << result << std::endl;

		auto package = con.RecvAll();
		switch (package->getId()) {
		case ErrorPackage::PACKAGE_ID: {
			auto errorPackage = dynamic_cast<ErrorPackage*>(package.get());
			int errorCode = errorPackage->getErrorCode();
			std::cout << "Recv failed with error: " << errorCode << std::endl;
			return;
		} break;
		default:
			std::cout << "Bytes received: " << package->getSize() << std::endl;
			dynamic_cast<PackableClass*>(package.get())->print();
			break;
		}
	} while (1);

	result = con.Disconnect();
	if (result == SOCKET_ERROR)
	{
		std::cout << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
	}

	ShutdownWinSock();
}