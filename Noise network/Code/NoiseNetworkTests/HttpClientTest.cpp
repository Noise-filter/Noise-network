#include "CppUnitTest.h"

#include "Core\WinsockFunctions.h"

#include "Extended\Http\HttpClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(HttpClientTest)
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

		TEST_METHOD(SetHostHttp)
		{
			string host = "http://www.sweclockers.com/";
			unsigned short port = 0;

			HttpClient client(host, port);

			Assert::AreEqual(string("www.sweclockers.com"), client.GetHostname());
			Assert::AreEqual((unsigned short)80, client.GetHost()->GetPort());
		}

		TEST_METHOD(SetHostHttps)
		{
			string host = "https://www.google.se/";
			unsigned short port = 0;

			HttpClient client(host, port);

			Assert::AreEqual(string("www.google.se"), client.GetHostname());
			Assert::AreEqual((unsigned short)443, client.GetHost()->GetPort());
		}

		TEST_METHOD(SendRequest)
		{
			string asd = "{\n"
				"  \"userId\": 1,\n"
				"  \"id\": 1,\n"
				"  \"title\": \"sunt aut facere repellat provident occaecati excepturi optio reprehenderit\",\n"
				"  \"body\": \"quia et suscipit\\nsuscipit recusandae consequuntur expedita et cum\\nreprehenderit molestiae ut ut quas totam\\nnostrum rerum est autem sunt rem eveniet architecto\"\n"
				"}";
			string host = "http://jsonplaceholder.typicode.com/";
			unsigned short port = 0;

			HttpClient client(host, port);

			Assert::AreEqual(string("jsonplaceholder.typicode.com"), client.GetHostname());
			Assert::AreEqual((unsigned short)80, client.GetHost()->GetPort());

			HttpResponse response = client.SendRequest(createRequest(GET, "/posts/1"));
			Assert::AreEqual(asd, response.GetBody());
		}

		HttpRequest createRequest(HttpMethod method, string uri = "/")
		{
			unsigned int majorVersion = 1;
			unsigned int minorVersion = 1;

			HttpRequest request(uri, method);
			request.SetHttpVersion(majorVersion, minorVersion);
			return request;
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