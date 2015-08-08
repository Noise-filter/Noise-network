#include "CppUnitTest.h"

#include "Extended\Http\HttpResponse.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(HttpResponseTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Before)
		{

		}

		TEST_CLASS_CLEANUP(After)
		{

		}

		TEST_METHOD(ParseCorrectResponse)
		{
			string textResponse = 
			"HTTP/1.1 200 OK\n"
			"Date: Fri, 31 Dec 1999 23:59:59 GMT\n"
			"Content-Type: text/html\n"
			"Content-Length: 1354\n"
			"\n"
			"<html>\n"
			"<body>\n"
			"<h1>Happy New Millennium!</h1>\n"
			"(more file contents)\n"
			".\n"
			".\n"
			".\n"
			"</body>\n"
			"</html>";
			HttpResponse response;

			unsigned int majorVersion = 1;
			unsigned int minorVersion = 1;

			response.parse(textResponse);
			
			Assert::AreEqual((int)Ok, (int)response.GetStatus());

			Assert::AreEqual(majorVersion, response.GetMajorHttpVersion());
			Assert::AreEqual(minorVersion, response.GetMinorHttpVersion());

			Assert::IsTrue(response.HasField("date"));
			Assert::AreEqual(string("Fri, 31 Dec 1999 23:59:59 GMT"), response.GetField("date"));

			Assert::IsTrue(response.HasField("content-type"));
			Assert::AreEqual(string("text/html"), response.GetField("content-type"));
			
			Assert::IsTrue(response.HasField("content-length"));
			Assert::AreEqual(string("1354"), response.GetField("content-length"));

			Assert::AreEqual(string("<html>\n"
				"<body>\n"
				"<h1>Happy New Millennium!</h1>\n"
				"(more file contents)\n"
				".\n"
				".\n"
				".\n"
				"</body>\n"
				"</html>"), response.GetBody());
		}

		TEST_METHOD(ParseInvalidResponse)
		{
			string textResponse =
				"HTTPS/1.1 200 OK\n"
				"Date: Fri, 31 Dec 1999 23:59:59 GMT\n"
				"Content-Type: text/html\n"
				"Content-Length: 1354\n"
				"\n"
				"<html>\n"
				"<body>\n"
				"<h1>Happy New Millennium!</h1>\n"
				"(more file contents)\n"
				".\n"
				".\n"
				".\n"
				"</body>\n"
				"</html>";
			HttpResponse response;

			response.parse(textResponse);

			Assert::AreEqual((int)InvalidResponse, (int)response.GetStatus());
		}

		TEST_METHOD(ParseInvalidResponse_NoStatus)
		{
			string textResponse =
				"HTTP/1.1 OK\n"
				"Date: Fri, 31 Dec 1999 23:59:59 GMT\n"
				"Content-Type: text/html\n"
				"Content-Length: 1354\n"
				"\n"
				"<html>\n"
				"<body>\n"
				"<h1>Happy New Millennium!</h1>\n"
				"(more file contents)\n"
				".\n"
				".\n"
				".\n"
				"</body>\n"
				"</html>";
			HttpResponse response;

			response.parse(textResponse);

			Assert::AreEqual((int)InvalidResponse, (int)response.GetStatus());
		}
	};
}