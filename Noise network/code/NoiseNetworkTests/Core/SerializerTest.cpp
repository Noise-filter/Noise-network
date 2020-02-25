#include "CppUnitTest.h"

#include <stdint.h>
#include <limits>

#include "Core\Serializer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace NoiseNetworkTests
{
	TEST_CLASS(SerializerTest)
	{
	public:
		TEST_METHOD(BoolTest)
		{
			std::vector<unsigned char> buffer;
			Serializer::Pack(false, buffer);
			Serializer::Pack(true, buffer);

			Assert::AreEqual((unsigned char)0, buffer[0]);
			Assert::AreEqual((unsigned char)1, buffer[1]);

			bool result;
			Serializer::Unpack(buffer, 0, result);
			Assert::AreEqual(false, result);
			Serializer::Unpack(buffer, 1, result);
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(CharTest)
		{
			TestSomeIntegerValues<char>();
		}

		TEST_METHOD(UnsignedCharTest)
		{
			TestSomeIntegerValues<unsigned char>();
		}

		TEST_METHOD(ShortTest)
		{
			TestSomeIntegerValues<short>();
		}

		TEST_METHOD(UnsignedShortTest)
		{
			TestSomeIntegerValues<unsigned short>();
		}

		TEST_METHOD(IntTest)
		{
			TestSomeIntegerValues<int>();
		}

		TEST_METHOD(UnsignedIntTest)
		{
			TestSomeIntegerValues<unsigned int>();
		}

		TEST_METHOD(LongLongTest)
		{
			TestSomeIntegerValues<long long>();
		}

		TEST_METHOD(UnsignedLongLongTest)
		{
			TestSomeIntegerValues<unsigned long long>();
		}

		TEST_METHOD(FloatTest)
		{
			TestSomeIntegerValues<float>();
		}

		TEST_METHOD(DoubleTest)
		{
			TestSomeIntegerValues<double>();
		}

		TEST_METHOD(StringTest_Normal)
		{
			std::vector<unsigned char> buffer;
			std::string str("Hello, How are you?""");
			
			Serializer::Pack(str, buffer);

			std::string result;
			Serializer::Unpack(buffer, 0, result);
			Assert::AreEqual(str, result);
		}

		TEST_METHOD(StringTest_Long)
		{
			std::vector<unsigned char> buffer;
			std::string str("Hello, How are you?epkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeee""");

			Serializer::Pack(str, buffer);

			std::string result;
			Serializer::Unpack(buffer, 0, result);
			Assert::AreEqual(str, result);
		}

		TEST_METHOD(StringTest_Empty)
		{
			std::vector<unsigned char> buffer;
			std::string str;

			Serializer::Pack(str, buffer);

			std::string result;
			Serializer::Unpack(buffer, 0, result);
			Assert::AreEqual(str, result);
		}

		TEST_METHOD(CStringTest_Normal)
		{
			std::vector<unsigned char> buffer;
			char* str{ "Hello, How are you?""" };

			Serializer::Pack(str, buffer);

			char result[21];
			Serializer::Unpack(buffer, 0, result);
			Assert::AreEqual(str, result);
		}

		TEST_METHOD(CStringTest_Long)
		{
			std::vector<unsigned char> buffer;
			char* str{ "Hello, How are you?epkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeeeepkogrgpokrkkkkkkkkkkkkkkkkkkkkkkkkkerrrrrreeeee""" };

			Serializer::Pack(str, buffer);
			Serializer::Pack(str, buffer);

			char result[15000];
			char result2[15000];
			int index = Serializer::Unpack(buffer, 0, result);
			index += Serializer::Unpack(buffer, index, result2);
			Assert::AreEqual(str, result);
		}

		TEST_METHOD(CStringTest_Empty)
		{
			std::vector<unsigned char> buffer;
			char* str{ "" };

			Serializer::Pack(str, buffer);

			char result[1];
			Serializer::Unpack(buffer, 0, result);
			Assert::AreEqual(str, result);
		}

		TEST_METHOD(VectorTestIterators_Normal)
		{
			std::vector<unsigned char> buffer;
			std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

			Serializer::Pack(data, buffer);

			std::vector<int> result;
			Serializer::Unpack(buffer, 0, result);
			AreContainersEqual<vector<int>>(data, result);
		}

		TEST_METHOD(VectorTestIterators_Empty)
		{
			std::vector<unsigned char> buffer;
			std::vector<int> data;

			Serializer::Pack(data, buffer);

			std::vector<int> result;
			Serializer::Unpack(buffer, 0, result);
			AreContainersEqual<vector<int>>(data, result);
		}

		TEST_METHOD(VariadicTemplates)
		{
			std::vector<unsigned char> buffer;
			Serializer::Pack(buffer, std::string("hello how are you?"), 12, 1.12345, std::vector<int>{1, 6, 9});

			string str;
			int integer;
			double doubleValue;
			std::vector<int> numbers;
			Serializer::Unpack(buffer, 0, str, integer, doubleValue, numbers);

			Assert::AreEqual(std::string("hello how are you?"), str);
			Assert::AreEqual(12, integer);
			Assert::AreEqual(1.12345, doubleValue);
			AreContainersEqual(std::vector<int>{1, 6, 9}, numbers);
		}

		TEST_METHOD(VariadicTemplates_SeperateUnpackCalls)
		{
			std::vector<unsigned char> buffer;
			Serializer::Pack(buffer, std::string("hello how are you?"), 12, 1.12345, std::vector<int>{1, 6, 9});

			string str;
			int integer;
			double doubleValue;
			std::vector<int> numbers;
			unsigned int index = Serializer::Unpack(buffer, 0, str);
			index = Serializer::Unpack(buffer, index, integer);
			index = Serializer::Unpack(buffer, index, doubleValue);
			index = Serializer::Unpack(buffer, index, numbers);

			Assert::AreEqual(std::string("hello how are you?"), str);
			Assert::AreEqual(12, integer);
			Assert::AreEqual(1.12345, doubleValue);
			AreContainersEqual(std::vector<int>{1, 6, 9}, numbers);
		}

	private:
		template<typename Type>
		void TestSomeIntegerValues()
		{
			Type min = std::numeric_limits<Type>::min();
			Type max = std::numeric_limits<Type>::max();
			std::vector<unsigned char> buffer;

			Serializer::Pack(static_cast<Type>(min), buffer);
			Serializer::Pack(static_cast<Type>(max), buffer);
			Serializer::Pack(static_cast<Type>(0), buffer);
			Serializer::Pack(static_cast<Type>(min/0.5), buffer);
			Serializer::Pack(static_cast<Type>(max*0.5), buffer);

			Type c;
			Serializer::Unpack(buffer, 0 * sizeof(Type), c);
			Assert::AreEqual(static_cast<Type>(min), c);
			Serializer::Unpack(buffer, 1 * sizeof(Type), c);
			Assert::AreEqual(static_cast<Type>(max), c);
			Serializer::Unpack(buffer, 2 * sizeof(Type), c);
			Assert::AreEqual(static_cast<Type>(0), c);
			Serializer::Unpack(buffer, 3 * sizeof(Type), c);
			Assert::AreEqual(static_cast<Type>(min/0.5), c);
			Serializer::Unpack(buffer, 4 * sizeof(Type), c);
			Assert::AreEqual(static_cast<Type>(max*0.5), c);
		}

		template<typename ContainerType>
		void AreContainersEqual(ContainerType expected, ContainerType actual)
		{
			ContainerType::const_iterator current(begin(expected)), end = std::end(expected);
			ContainerType::const_iterator current2(begin(actual)), end2 = std::end(actual);
			size_t size = expected.size();
			size_t size2 = actual.size();
			Assert::AreEqual(size, size2);
			for (; current != end && current2 != end2; ++current, ++current2)
			{
				Assert::AreEqual(*current, *current2);
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