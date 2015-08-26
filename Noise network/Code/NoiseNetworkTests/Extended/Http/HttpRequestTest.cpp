#include "CppUnitTest.h"

#include "Extended\Http\HttpRequest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(HttpRequestTest)
	{
	public:
		TEST_METHOD(GeneralHttpRequest)
		{
			HttpVersion version(1, 1);
			string body = "{\"id\": \"file\"}";
			HttpMethod method = POST;
			string uri = "/devices/testDevice";

			HttpRequest request("/devices/testDevice", method, body);
			request.SetHttpVersion(version);
			request.SetField("name", "value");
			request.SetField("length", "123");
			
			Assert::AreEqual(string("POST /devices/testDevice HTTP/1.1\r\nlength: 123\r\nname: value\r\n\r\n{\"id\": \"file\"}"), request.GetRequestAsString());
			Assert::IsTrue(request.HasField("name"));
			Assert::AreEqual(string("value"), request.GetField("name"));
			Assert::IsTrue(request.HasField("length"));
			Assert::AreEqual(string("123"), request.GetField("length"));
			Assert::IsFalse(request.HasField("asd"));
			Assert::AreEqual(version, request.getVersion());
			Assert::AreEqual(body, request.GetBody());
			Assert::AreEqual((int)method, (int)request.getMethod());
			Assert::AreEqual(uri, request.GetUri());
		}

		TEST_METHOD(EveryHttpMethod)
		{
			HttpRequest request("/", GET, "BODY");

			Assert::AreEqual(request.GetRequestAsString(), string("GET / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(HEAD);
			Assert::AreEqual(request.GetRequestAsString(), string("HEAD / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(POST);
			Assert::AreEqual(request.GetRequestAsString(), string("POST / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(PUT);
			Assert::AreEqual(request.GetRequestAsString(), string("PUT / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(DELETE_);
			Assert::AreEqual(request.GetRequestAsString(), string("DELETE / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(TRACE);
			Assert::AreEqual(request.GetRequestAsString(), string("TRACE / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(OPTIONS);
			Assert::AreEqual(request.GetRequestAsString(), string("OPTIONS / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(CONNECT);
			Assert::AreEqual(request.GetRequestAsString(), string("CONNECT / HTTP/1.0\r\n\r\nBODY"));
			request.SetMethod(PATCH);
			Assert::AreEqual(request.GetRequestAsString(), string("PATCH / HTTP/1.0\r\n\r\nBODY"));
		}

		TEST_METHOD(InvalidHttpMethod)
		{
			HttpRequest request("/", (HttpMethod)-14, "BODY");
			try 
			{
				string str = request.GetRequestAsString();

				Assert::Fail(L"No exception encountered. Expected ParseException", LINE_INFO());
			}
			catch (ParseException e)
			{
				
			}
			catch (...)
			{
				Assert::Fail(L"Wrong exception caught. Expected ParseException", LINE_INFO());
			}
		}

		TEST_METHOD(UriNoStartingWithSlash)
		{
			HttpRequest request("devices/testDevice", GET);
			Assert::AreEqual(request.GetUri(), string("/devices/testDevice"));

			request.SetUri("devices/testDevice");
			Assert::AreEqual(request.GetUri(), string("/devices/testDevice"));
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

			template<>
			static std::wstring ToString<HttpVersion>(const HttpVersion& t)
			{
				wstring str = ToString(t.getMajorVersion()) + L"." + ToString(t.getMinorVersion());
				RETURN_WIDE_STRING(str);
			}
		}
	}
}