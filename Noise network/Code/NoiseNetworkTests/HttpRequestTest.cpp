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
			unsigned int majorVersion = 1;
			unsigned int minorVersion = 1;
			string body = "{\"id\": \"file\"}";
			HttpMethod method = POST;
			string uri = "/devices/testDevice";

			HttpRequest request("/devices/testDevice", method, body);
			request.SetHttpVersion(majorVersion, minorVersion);
			request.SetField("name", "value");
			request.SetField("length", "123");
			
			Assert::AreEqual(request.GetRequestAsString(), string("POST /devices/testDevice HTTP/1.1\r\nlength: 123\r\nname: value\r\n\r\n{\"id\": \"file\"}"));
			Assert::IsTrue(request.HasField("name"));
			Assert::AreEqual(request.GetField("name"), string("value"));
			Assert::IsTrue(request.HasField("length"));
			Assert::AreEqual(request.GetField("length"), string("123"));
			Assert::IsFalse(request.HasField("asd"));
			Assert::AreEqual(request.getMajorVersion(), majorVersion);
			Assert::AreEqual(request.getMinorVersion(), minorVersion);
			Assert::AreEqual(request.GetBody(), body);
			Assert::AreEqual((int)request.getMethod(), (int)method);
			Assert::AreEqual(request.GetUri(), uri);
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