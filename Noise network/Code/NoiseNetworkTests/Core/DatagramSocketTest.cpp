#include "CppUnitTest.h"

#include "Core\WinsockFunctions.h"

#include "Core\SocketAddress.h"
#include "Core\DatagramSocket.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(DatagramSocketTest)
	{
	public:
		DatagramSocketTest()
		{
			serverAddress = SocketAddressFactory::Create(serverIp, serverPort);
		}

		~DatagramSocketTest()
		{
		}

		TEST_METHOD_INITIALIZE(Before)
		{

		}

		TEST_CLASS_INITIALIZE(BeforeClass)
		{
			InitWinSock();
		}

		TEST_CLASS_CLEANUP(AfterClass)
		{
			ShutdownWinSock();
		}

		TEST_METHOD(BindAndInitSocket)
		{
			DatagramSocket socket;
			createSocket(socket, "0.0.0.0", 0);
			Assert::IsTrue(socket.IsInitialized());

			DatagramSocket serverSocket;
			createSocket(serverSocket, "0.0.0.0", serverPort);
			Assert::IsTrue(serverSocket.IsInitialized());

			socket.Close();
			serverSocket.Close();
		}

		TEST_METHOD(SendPacketBackAndForth)
		{
			SocketAddress bindAddress = SocketAddressFactory::Create("0.0.0.0", serverPort);

			DatagramSocket socket;
			createSocket(socket, "0.0.0.0", 0);
			Assert::IsTrue(socket.IsInitialized());

			DatagramSocket serverSocket;
			createSocket(serverSocket, "0.0.0.0", serverPort);
			Assert::IsTrue(serverSocket.IsInitialized());

			string message = "TESTING testing";
			vector<char> buffer;
			buffer.assign(message.begin(), message.end());

			int result = socket.Send(serverAddress, buffer, buffer.size());
			if (result == SOCKET_ERROR)
			{
				Assert::Fail(L"Send failed with error code: " + WSAGetLastError());
			}

			buffer.clear();
			buffer.resize(1024);

			result = serverSocket.Recv(bindAddress, buffer, 1024);
			if (result == SOCKET_ERROR)
			{
				Assert::Fail(L"Recv failed with error code: " + WSAGetLastError());
			}

			string resultString = buffer.data();
			Assert::AreEqual(message, resultString);
			Assert::AreEqual((int)message.size(), result);

			socket.Close();
			serverSocket.Close();
		}

		TEST_METHOD(SocketIsNotInitialized)
		{
			DatagramSocket socket;
			Assert::IsFalse(socket.IsInitialized());
		}

		TEST_METHOD(CallBindBeforeInitShouldReturnFalse)
		{
			DatagramSocket socket;
			bool result = socket.Bind(SocketAddressFactory::Create("0.0.0.0", 0));

			Assert::IsFalse(result);
		}

	private:
		void createSocket(DatagramSocket& socket, string ip = "0.0.0.0", unsigned short port = 0)
		{
			SocketAddress bindAddress = SocketAddressFactory::Create(ip, port);

			if (!socket.Init(bindAddress->GetFamily()))
			{
				Assert::Fail(L"socket.Init() failed");
			}

			if (!socket.Bind(bindAddress))
			{
				Assert::Fail(L"socket.Bind() failed");
			}
		}

	private:
		SocketAddress serverAddress;
		string serverIp = "127.0.0.1";
		unsigned short serverPort = 61000;

	};
}

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<type_info>(const type_info& t)
			{
				RETURN_WIDE_STRING(t.raw_name());
			}

			template<>
			static std::wstring ToString<unsigned short>(const unsigned short& t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}