#include "CppUnitTest.h"

#include "Core\WinsockFunctions.h"

#include "Core\SocketAddress.h"
#include "Core\SocketAddress\SocketAddressIPv4.h"
#include "Core\SocketAddress\SocketAddressIPv6.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NoiseNetworkTests
{
	TEST_CLASS(SocketAddressFactoryTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Before)
		{
			InitWinSock();
		}

		TEST_CLASS_CLEANUP(After)
		{
			ShutdownWinSock();
		}
		
		TEST_METHOD(CreateIPv4FromFamily)
		{
			std::string ip("0.0.0.0");
			unsigned short port = 0;
			short family = AF_INET;
			auto addr = SocketAddressFactory::Create(family);

			AssertSocketAddress<SocketAddressIPv4>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateIPv6FromFamily)
		{
			std::string ip("::");
			unsigned short port = 0;
			short family = AF_INET6;
			auto addr = SocketAddressFactory::Create(family);

			AssertSocketAddress<SocketAddressIPv6>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateBroadcastAddress)
		{
			std::string ip("255.255.255.255");
			unsigned short port = 0;
			short family = AF_INET;
			auto addr = SocketAddressFactory::Create(ip, port);

			AssertSocketAddress<SocketAddressIPv4>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateFromInvalidFamily)
		{
			auto addr = SocketAddressFactory::Create(0);
			Assert::IsNull(addr.get());
		}

		TEST_METHOD(CreateIPv4FromAddress)
		{
			std::string ip("127.0.0.1");
			unsigned short port = 12345;
			short family = AF_INET;

			auto addr = SocketAddressFactory::Create(ip, port);

			AssertSocketAddress<SocketAddressIPv4>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateIPv6FromAddress)
		{
			std::string ip("::1");
			unsigned short port = 12345;
			short family = AF_INET6;

			auto addr = SocketAddressFactory::Create(ip, port);

			AssertSocketAddress<SocketAddressIPv6>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateWithInvalidIP)
		{
			std::string ip("not an ip");
			auto addr = SocketAddressFactory::Create(ip);
			Assert::IsNull(addr.get());
		}

		TEST_METHOD(CreateFromSockaddr_in)
		{
			std::string ip("127.0.0.1");
			unsigned short port = 12345;
			short family = AF_INET;

			sockaddr_in sa;
			inet_pton(family, ip.c_str(), &sa.sin_addr);
			sa.sin_port = htons(port);
			sa.sin_family = family;

			auto addr = SocketAddressFactory::Create(sa);

			AssertSocketAddress<SocketAddressIPv4>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateFromSockaddr_inInvalidFamily)
		{
			std::string ip("127.0.0.1");
			unsigned short port = 12345;
			short family = AF_INET6;

			sockaddr_in sa;
			inet_pton(family, ip.c_str(), &sa.sin_addr);
			sa.sin_port = htons(port);
			sa.sin_family = family;

			auto addr = SocketAddressFactory::Create(sa);

			Assert::IsNull(addr.get());
		}

		TEST_METHOD(CreateFromSockaddr_in6)
		{
			std::string ip("::1");
			unsigned short port = 12345;
			short family = AF_INET6;

			sockaddr_in6 sa6;
			inet_pton(family, ip.c_str(), &sa6.sin6_addr);
			sa6.sin6_port = htons(port);
			sa6.sin6_family = family;

			auto addr = SocketAddressFactory::Create(sa6);

			AssertSocketAddress<SocketAddressIPv6>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateFromSockaddr_in6InvalidFamily)
		{
			std::string ip("::1");
			unsigned short port = 12345;
			short family = AF_INET;

			sockaddr_in6 sa6;
			inet_pton(family, ip.c_str(), &sa6.sin6_addr);
			sa6.sin6_port = htons(port);
			sa6.sin6_family = family;

			auto addr = SocketAddressFactory::Create(sa6);

			Assert::IsNull(addr.get());
		}

		TEST_METHOD(CreateIPv4FromSockaddr)
		{
			std::string ip("127.0.0.1");
			unsigned short port = 0;
			short family = AF_INET;
			addrinfo* addrResult = NULL;

			int result = getaddrinfo(ip.c_str(), NULL, NULL, &addrResult);
			auto addr = SocketAddressFactory::Create(*addrResult->ai_addr);

			AssertSocketAddress<SocketAddressIPv4>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateIPv6FromSockaddr)
		{
			std::string ip("::1");
			unsigned short port = 0;
			short family = AF_INET6;
			addrinfo* addrResult = NULL;

			int result = getaddrinfo(ip.c_str(), NULL, NULL, &addrResult);
			auto addr = SocketAddressFactory::Create(*addrResult->ai_addr);

			AssertSocketAddress<SocketAddressIPv6>(*addr, ip, port, family);
		}

		TEST_METHOD(CreateSockaddr_InvalidFamily)
		{
			std::string ip("::1");
			unsigned short port = 0;
			short family = AF_UNSPEC;
			addrinfo* addrResult = NULL;

			int result = getaddrinfo(ip.c_str(), NULL, NULL, &addrResult);
			addrResult->ai_addr->sa_family = family;

			auto addr = SocketAddressFactory::Create(*addrResult->ai_addr);

			Assert::IsNull(addr.get());
		}

		TEST_METHOD(CreateFromSocket_InvalidSocket)
		{
			auto addr = SocketAddressFactory::CreateFromSocket(INVALID_SOCKET);
			Assert::IsNull(addr.get());
		}

		TEST_METHOD(CreateFromSocket_NotValidSocket)
		{
			auto addr = SocketAddressFactory::CreateFromSocket(-5);
			Assert::IsNull(addr.get());
		}

	private:
		//Helper function
		template<class T>
		void AssertSocketAddress(const SocketAddressInterface& addr, std::string ip, unsigned short port, short family)
		{
			Assert::AreEqual(typeid(T), typeid(addr));
			Assert::AreEqual(ip, addr.GetIP());
			Assert::AreEqual(port, addr.GetPort());
			Assert::AreEqual(family, addr.GetFamily());
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