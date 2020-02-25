#include "../ClientExamples.h"

#include <iostream>
#include <string>
#include <chrono>

#include "Core\WinsockFunctions.h"
#include "Core\StreamConnection.h"

#include "Core\SocketAddress.h"
#include "Core\Package\PackageFactory.h"

#include "PackableClass.h"

constexpr auto bits(long long bytes, long long time) -> long long;
constexpr long long kiloBits(long long bytes, long long time);
constexpr long long megaBits(long long bytes, long long time);

void ClientExamples::SimpleMessageClient_ImplementedWithStreamConnection(std::string address, unsigned short port)
{
	if (InitWinSock())
	{
		return;
	}

	std::cout << "Hello World!" << std::endl;

	PackageFactory::getInstance().registerPackage(0, []() { return std::make_unique<PackableClass>(); });

	auto addr = SocketAddressFactory::Create(address, port);
	StreamConnection con;
	if (!con.Connect(std::move(addr)))
	{
		std::cout << "Error connecting" << std::endl;
		return;
	}

	using namespace std::chrono_literals;
	long long bytesSent{ 0 };
	long long bytesRecived{ 0 };
	auto currentTime{ std::chrono::steady_clock::now() };
	auto startTime = currentTime;

	int result = 0;
	PackableClass person;
	do
	{
		result = con.SendAll(person);
		if (result == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			break;
		}

		bytesSent += result;
		//std::cout << "Bytes sent: " << result << std::endl;

		auto package = con.RecvAll();
		switch (package->getId()) {
		case ErrorPackage::PACKAGE_ID: {
			auto errorPackage = static_cast<ErrorPackage*>(package.get());
			auto errorCode = errorPackage->getErrorCode();
			std::cout << "Recv failed with error: " << static_cast<typename std::underlying_type<PackageErrors>::type>(errorCode) << std::endl;
			return;
		} break;
		default:
			if (result != package->getSize()) {
				std::cout << "Error sent size doesn't match recived size" << std::endl;
			}
			bytesRecived += package->getSize();
			//std::cout << "Bytes received: " << package->getSize() << std::endl;
			//static_cast<PackableClass*>(package.get())->print();
			break;
		}
		auto newTime = std::chrono::steady_clock::now();
		auto delta = newTime - currentTime;
		if (delta >= 1s) {
			currentTime = newTime;
			auto time = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
			std::cout << bits(bytesSent, time) << " b/s " << 
				kiloBits(bytesSent, time) << "Kb/s " << 
				megaBits(bytesSent, time) << " Mb/s" << std::endl;
			bytesSent = bytesRecived = 0;
			startTime = currentTime;
		}
	} while (1);

	result = con.Disconnect();
	if (result == SOCKET_ERROR)
	{
		std::cout << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
	}

	ShutdownWinSock();
}

constexpr auto bits(long long bytes, long long time) -> long long {
	return (bytes * 8) / time;
}

constexpr long long kiloBits(long long bytes, long long time) {
	return ((bytes * 8) / time) / 1000;
}

constexpr long long megaBits(long long bytes, long long time) {
	return ((bytes * 8) / time) / 1000000;
}