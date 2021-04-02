#include "CppUnitTest.h"

#include <iostream>
#include "Core\WinsockFunctions.h"

#include "Core\ThreadedAcceptServer.h"
#include "Core\StreamSocket.h"
#include "Core\SocketAddress.h"
#include "Core\SocketAddress\SocketAddressIPv4.h"
#include "Core\SocketAddress\SocketAddressIPv6.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(ThreadedAcceptServerTest)
	{
	public:
		const unsigned short port = 7878;
		const string ip = "127.0.0.1";

		TEST_METHOD_INITIALIZE(Before)
		{
			InitWinSock();
		}

		TEST_METHOD_CLEANUP(After)
		{
			ShutdownWinSock();
		}

		TEST_METHOD(StatusesBeforeDoingAnything)
		{
			ThreadedAcceptServer server;
			Assert::IsFalse(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());
		}
		
		TEST_METHOD(InitAndStop)
		{
			ThreadedAcceptServer server;
			if (!server.Init(*SocketAddressFactory::Create("0.0.0.0")))
			{
				Assert::Fail();
			}
			Assert::IsTrue(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());
		
			server.Stop(true);
			Assert::IsFalse(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());
		}

		TEST_METHOD(InitStartStop)
		{
			ThreadedAcceptServer server;
			if (!server.Init(*SocketAddressFactory::Create("0.0.0.0")))
			{
				Assert::Fail();
			}
			Assert::IsTrue(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());

			server.Start();
			Assert::IsTrue(server.IsInitialized());
			Sleep(500);
			Assert::IsTrue(server.IsStarted());

			server.Stop(true);
			Assert::IsFalse(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());
		}
		
		TEST_METHOD(StopTheServerBeforeItIsStarted)
		{
			ThreadedAcceptServer server;
			Assert::IsFalse(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());
			server.Stop(false);
			server.Stop(true);
			server.Stop(true);
			Assert::IsFalse(server.IsInitialized());
			Assert::IsFalse(server.IsStarted());
		}
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