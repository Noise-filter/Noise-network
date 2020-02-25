#include "CppUnitTest.h"

#include "Core\WinsockFunctions.h"
#include "Core\DatagramSocket.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(WinsockFunctionTest)
	{
	public:
		TEST_CLASS_INITIALIZE(BeforeClass)
		{
			ShutdownWinSock();
		}

		TEST_METHOD(GetLastSystemErrorTest)
		{
			DatagramSocket socket;
			if (!socket.Init(AF_INET))
			{
				int error = GetLastSystemError();
				Assert::AreEqual(10093, error);
			}
			else
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(GetErrorMessageTest)
		{
			DatagramSocket socket;
			if (!socket.Init(AF_INET))
			{
				std::string msg = GetErrorMessage(GetLastSystemError());
				Assert::AreEqual(std::string("Either the application has not called WSAStartup, or WSAStartup failed.\r\n"), msg);
			}
			else
			{
				Assert::Fail();
			}
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