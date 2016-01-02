#include "CppUnitTest.h"

#include "Utilities\StringUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(StringUtilsTest)
	{
	public:
		string testString = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

		TEST_METHOD(toUpperCaseTest)
		{
			string result = toUpperCase(testString);
			Assert::AreEqual(string(" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~"), result);
		}

		TEST_METHOD(toLowerCaseTest)
		{
			string result = toLowerCase(testString);
			Assert::AreEqual(string(" !\"#$%&\'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"), result);
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