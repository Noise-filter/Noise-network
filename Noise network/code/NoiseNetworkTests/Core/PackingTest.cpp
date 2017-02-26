#include "CppUnitTest.h"

#include "Core\Packing.h"
#include <vector>
#include <string>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(PackingTest)
	{
	public:
		TEST_METHOD(PackBoolFalse)
		{
			std::vector<unsigned char> buffer = Packing::pack(false);
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)0, buffer.at(0));
		}

		TEST_METHOD(PackBoolTrue)
		{
			std::vector<unsigned char> buffer = Packing::pack(true);
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)1, buffer.at(0));
		}

		TEST_METHOD(PackChar)
		{
			std::vector<unsigned char> buffer = Packing::pack('A');
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)'A', buffer.at(0));
		}

		TEST_METHOD(PackCharMin)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::numeric_limits<char>::lowest());
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)std::numeric_limits<char>::lowest(), buffer.at(0));
		}

		TEST_METHOD(PackCharMax)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::numeric_limits<char>::max());
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)std::numeric_limits<char>::max(), buffer.at(0));
		}

		TEST_METHOD(PackUnsignedChar)
		{
			std::vector<unsigned char> buffer = Packing::pack((unsigned char)'A');
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)'A', buffer.at(0));
		}

		TEST_METHOD(PackUnsignedCharMin)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::numeric_limits<unsigned char>::lowest());
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)std::numeric_limits<unsigned char>::lowest(), buffer.at(0));
		}

		TEST_METHOD(PackUnsignedCharMax)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::numeric_limits<unsigned char>::max());
			Assert::AreEqual((size_t)1, buffer.size());
			Assert::AreEqual((unsigned char)std::numeric_limits<unsigned char>::max(), buffer.at(0));
		}

		TEST_METHOD(PackShort)
		{
			std::vector<unsigned char> buffer = Packing::pack((short)1234);
			Assert::AreEqual((size_t)2, buffer.size());
			Assert::AreEqual((unsigned char)4, buffer.at(0));
			Assert::AreEqual((unsigned char)210, buffer.at(1));
		}

		TEST_METHOD(PackShortMin)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::numeric_limits<short>::lowest());
			Assert::AreEqual((size_t)2, buffer.size());
			Assert::AreEqual((unsigned char)128, buffer.at(0));
			Assert::AreEqual((unsigned char)0, buffer.at(1));
		}

		TEST_METHOD(PackShortMax)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::numeric_limits<short>::max());
			Assert::AreEqual((size_t)2, buffer.size());
			Assert::AreEqual((unsigned char)127, buffer.at(0));
			Assert::AreEqual((unsigned char)255, buffer.at(1));
		}

		TEST_METHOD(PackUnsignedShort)
		{
			std::vector<unsigned char> buffer = Packing::pack((unsigned short)1234);
			Assert::AreEqual((size_t)2, buffer.size());
			Assert::AreEqual((unsigned char)4, buffer.at(0));
			Assert::AreEqual((unsigned char)210, buffer.at(1));
		}

		TEST_METHOD(PackInt)
		{
			std::vector<unsigned char> buffer = Packing::pack((int)123454355);
			Assert::AreEqual((size_t)4, buffer.size());
			Assert::AreEqual((unsigned char)7, buffer.at(0));
			Assert::AreEqual((unsigned char)91, buffer.at(1));
			Assert::AreEqual((unsigned char)195, buffer.at(2));
			Assert::AreEqual((unsigned char)147, buffer.at(3));
		}

		TEST_METHOD(PackUnsignedInt)
		{
			std::vector<unsigned char> buffer = Packing::pack((unsigned int)123454355);
			Assert::AreEqual((size_t)4, buffer.size());
			Assert::AreEqual((unsigned char)7, buffer.at(0));
			Assert::AreEqual((unsigned char)91, buffer.at(1));
			Assert::AreEqual((unsigned char)195, buffer.at(2));
			Assert::AreEqual((unsigned char)147, buffer.at(3));
		}

		TEST_METHOD(PackInt64)
		{
			std::vector<unsigned char> buffer = Packing::pack((__int64)123454355123141235);
			Assert::AreEqual((size_t)8, buffer.size());
			Assert::AreEqual((unsigned char)1, buffer.at(0));
			Assert::AreEqual((unsigned char)182, buffer.at(1));
			Assert::AreEqual((unsigned char)153, buffer.at(2));
			Assert::AreEqual((unsigned char)20, buffer.at(3));
			Assert::AreEqual((unsigned char)247, buffer.at(4));
			Assert::AreEqual((unsigned char)22, buffer.at(5));
			Assert::AreEqual((unsigned char)250, buffer.at(6));
			Assert::AreEqual((unsigned char)115, buffer.at(7));
		}

		TEST_METHOD(PackUnsignedInt64)
		{
			std::vector<unsigned char> buffer = Packing::pack((unsigned __int64)123454355123141235);
			Assert::AreEqual((size_t)8, buffer.size());
			Assert::AreEqual((unsigned char)1, buffer.at(0));
			Assert::AreEqual((unsigned char)182, buffer.at(1));
			Assert::AreEqual((unsigned char)153, buffer.at(2));
			Assert::AreEqual((unsigned char)20, buffer.at(3));
			Assert::AreEqual((unsigned char)247, buffer.at(4));
			Assert::AreEqual((unsigned char)22, buffer.at(5));
			Assert::AreEqual((unsigned char)250, buffer.at(6));
			Assert::AreEqual((unsigned char)115, buffer.at(7));
		}

		TEST_METHOD(PackFloat)
		{
			std::vector<unsigned char> buffer = Packing::pack((float)1235.4663f);
			Assert::AreEqual((size_t)4, buffer.size());
			Assert::AreEqual((unsigned char)68, buffer.at(0));
			Assert::AreEqual((unsigned char)154, buffer.at(1));
			Assert::AreEqual((unsigned char)110, buffer.at(2));
			Assert::AreEqual((unsigned char)236, buffer.at(3));
		}

		TEST_METHOD(PackFloat0)
		{
			std::vector<unsigned char> buffer = Packing::pack((float)0);
			Assert::AreEqual((size_t)4, buffer.size());
			Assert::AreEqual((unsigned char)0, buffer.at(0));
			Assert::AreEqual((unsigned char)0, buffer.at(1));
			Assert::AreEqual((unsigned char)0, buffer.at(2));
			Assert::AreEqual((unsigned char)0, buffer.at(3));
		}

		TEST_METHOD(PackDouble)
		{
			std::vector<unsigned char> buffer = Packing::pack((double)1235.4663f);
			Assert::AreEqual((size_t)8, buffer.size());
			Assert::AreEqual((unsigned char)64, buffer.at(0));
			Assert::AreEqual((unsigned char)147, buffer.at(1));
			Assert::AreEqual((unsigned char)77, buffer.at(2));
			Assert::AreEqual((unsigned char)221, buffer.at(3));
			Assert::AreEqual((unsigned char)128, buffer.at(4));
			Assert::AreEqual((unsigned char)0, buffer.at(5));
			Assert::AreEqual((unsigned char)0, buffer.at(6));
			Assert::AreEqual((unsigned char)0, buffer.at(7));
		}

		TEST_METHOD(PackCString)
		{
			char str[] = "asd";
			std::vector<unsigned char> buffer = Packing::pack(str);
			Assert::AreEqual((size_t)5, buffer.size());
			Assert::AreEqual((unsigned char)0, buffer.at(0));
			Assert::AreEqual((unsigned char)3, buffer.at(1));
			Assert::AreEqual((unsigned char)'a', buffer.at(2));
			Assert::AreEqual((unsigned char)'s', buffer.at(3));
			Assert::AreEqual((unsigned char)'d', buffer.at(4));
		}

		TEST_METHOD(PackString)
		{
			std::vector<unsigned char> buffer = Packing::pack(std::string("asd"));
			Assert::AreEqual((size_t)5, buffer.size());
			Assert::AreEqual((unsigned char)0, buffer.at(0));
			Assert::AreEqual((unsigned char)3, buffer.at(1));
			Assert::AreEqual((unsigned char)'a', buffer.at(2));
			Assert::AreEqual((unsigned char)'s', buffer.at(3));
			Assert::AreEqual((unsigned char)'d', buffer.at(4));
		}

		TEST_METHOD(UnpackBool)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)1);
			bool value = Packing::unpackb(buffer.data());
			Assert::IsTrue(value);
		}

		TEST_METHOD(UnpackChar)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)'A');
			char value = Packing::unpackc(buffer.data());
			Assert::AreEqual('A', value);
		}

		TEST_METHOD(UnpackUnsignedChar)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)'A');
			unsigned char value = Packing::unpackC(buffer.data());
			Assert::AreEqual((unsigned char)'A', value);
		}

		TEST_METHOD(UnpackShort)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)4);
			buffer.push_back((unsigned char)210);
			short value = Packing::unpacks(buffer.data());
			Assert::AreEqual((short)1234, value);
		}

		TEST_METHOD(UnpackUnsignedShort)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)4);
			buffer.push_back((unsigned char)210);
			unsigned short value = Packing::unpackS(buffer.data());
			Assert::AreEqual((unsigned short)1234, value);
		}

		TEST_METHOD(UnpackInt)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)7);
			buffer.push_back((unsigned char)91);
			buffer.push_back((unsigned char)195);
			buffer.push_back((unsigned char)147);
			int value = Packing::unpacki(buffer.data());
			Assert::AreEqual((int)123454355, value);
		}

		TEST_METHOD(UnpackUnsignedInt)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)7);
			buffer.push_back((unsigned char)91);
			buffer.push_back((unsigned char)195);
			buffer.push_back((unsigned char)147);
			unsigned int value = Packing::unpackI(buffer.data());
			Assert::AreEqual((unsigned int)123454355, value);
		}

		TEST_METHOD(UnpackInt64)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)1);
			buffer.push_back((unsigned char)182);
			buffer.push_back((unsigned char)153);
			buffer.push_back((unsigned char)20);
			buffer.push_back((unsigned char)247);
			buffer.push_back((unsigned char)22);
			buffer.push_back((unsigned char)250);
			buffer.push_back((unsigned char)115);
			__int64 value = Packing::unpacki64(buffer.data());
			Assert::AreEqual((__int64)123454355123141235, value);
		}

		TEST_METHOD(UnpackUnsignedInt64)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)1);
			buffer.push_back((unsigned char)182);
			buffer.push_back((unsigned char)153);
			buffer.push_back((unsigned char)20);
			buffer.push_back((unsigned char)247);
			buffer.push_back((unsigned char)22);
			buffer.push_back((unsigned char)250);
			buffer.push_back((unsigned char)115);
			unsigned __int64 value = Packing::unpackI64(buffer.data());
			Assert::AreEqual((unsigned __int64)123454355123141235, value);
		}

		TEST_METHOD(UnpackFloat)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)68);
			buffer.push_back((unsigned char)154);
			buffer.push_back((unsigned char)110);
			buffer.push_back((unsigned char)236);
			float value = Packing::unpackf(buffer.data());
			Assert::AreEqual((float)1235.4663f, value);
		}

		TEST_METHOD(UnpackDouble)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)64);
			buffer.push_back((unsigned char)147);
			buffer.push_back((unsigned char)77);
			buffer.push_back((unsigned char)221);
			buffer.push_back((unsigned char)128);
			buffer.push_back((unsigned char)0);
			buffer.push_back((unsigned char)0);
			buffer.push_back((unsigned char)0);
			double value = Packing::unpackd(buffer.data());
			Assert::AreEqual((double)1235.4663f, value);
		}

		TEST_METHOD(UnpackCString)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)0);
			buffer.push_back((unsigned char)3);
			buffer.push_back((unsigned char)'a');
			buffer.push_back((unsigned char)'s');
			buffer.push_back((unsigned char)'d');
			char* value = Packing::unpackCStr(buffer.data());
			Assert::AreEqual((size_t)3, strlen(value));
			Assert::AreEqual("asd", value);
		}

		TEST_METHOD(UnpackString)
		{
			std::vector<unsigned char> buffer;
			buffer.push_back((unsigned char)0);
			buffer.push_back((unsigned char)3);
			buffer.push_back((unsigned char)'a');
			buffer.push_back((unsigned char)'s');
			buffer.push_back((unsigned char)'d');
			std::string value = Packing::unpackStr(buffer.data());
			Assert::AreEqual((size_t)3, value.size());
			Assert::AreEqual(std::string("asd"), value);
		}

		TEST_METHOD(PackUnpackBool)
		{
			bool a = true;
			bool b = Packing::unpackb(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackChar)
		{
			char a = 'a';
			char b = Packing::unpackc(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackUnsignedChar)
		{
			unsigned char a = 'a';
			unsigned char b = Packing::unpackC(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackShort)
		{
			short a = 12345;
			short b = Packing::unpacks(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackUnsignedShort)
		{
			unsigned short a = 12345;
			unsigned short b = Packing::unpackS(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackInt)
		{
			int a = 12345678;
			int b = Packing::unpacki(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackUnsignedInt)
		{
			unsigned int a = 12345678;
			unsigned int b = Packing::unpackI(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackInt64)
		{
			__int64 a = 1234567890;
			__int64 b = Packing::unpacki64(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackUnsignedInt64)
		{
			unsigned __int64 a = 1234567890;
			unsigned __int64 b = Packing::unpackI64(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackfloat)
		{
			float a = 123.123f;
			float b = Packing::unpackf(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackDouble)
		{
			double a = 12345.21454;
			double b = Packing::unpackd(Packing::pack(a).data());
			Assert::AreEqual(a, b);
		}

		TEST_METHOD(PackUnpackCString)
		{
			char a[] = "asd";
			char* b = Packing::unpackCStr(Packing::pack(a).data());
			Assert::AreEqual(a, b);
			delete[] b;
		}

		TEST_METHOD(PackUnpackString)
		{
			string a = "asd";
			string b = Packing::unpackStr(Packing::pack(a).data());
			Assert::AreEqual(a, b);
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

			std::wstring ToString(__int64 const& value)
			{
				return std::to_wstring(value);
			}
		}
	}
}