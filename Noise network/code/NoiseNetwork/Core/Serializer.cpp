#include "Serializer.h"

#include <algorithm>

void Serializer::Pack(const bool i, std::vector<unsigned char>& buffer)
{
	buffer.push_back(i);
}

void Serializer::Pack(const char i, std::vector<unsigned char>& buffer)
{
	buffer.push_back(i);
}

void Serializer::Pack(const unsigned char i, std::vector<unsigned char>& buffer)
{
	buffer.push_back(i);
}

void Serializer::Pack(const short i, std::vector<unsigned char>& buffer)
{
	buffer.push_back((unsigned char)(i >> 8));
	buffer.push_back((unsigned char)i);
}

void Serializer::Pack(const unsigned short i, std::vector<unsigned char>& buffer)
{
	buffer.push_back((unsigned char)(i >> 8));
	buffer.push_back((unsigned char)i);
}

void Serializer::Pack(const int i, std::vector<unsigned char>& buffer)
{
	buffer.push_back((unsigned char)(i >> 24));
	buffer.push_back((unsigned char)(i >> 16));
	buffer.push_back((unsigned char)(i >> 8));
	buffer.push_back((unsigned char)i);
}

void Serializer::Pack(const unsigned int i, std::vector<unsigned char>& buffer)
{
	buffer.push_back((unsigned char)(i >> 24));
	buffer.push_back((unsigned char)(i >> 16));
	buffer.push_back((unsigned char)(i >> 8));
	buffer.push_back((unsigned char)i);
}

void Serializer::Pack(const long long i, std::vector<unsigned char>& buffer)
{
	buffer.push_back((unsigned char)(i >> 56));
	buffer.push_back((unsigned char)(i >> 48));
	buffer.push_back((unsigned char)(i >> 40));
	buffer.push_back((unsigned char)(i >> 32));
	buffer.push_back((unsigned char)(i >> 24));
	buffer.push_back((unsigned char)(i >> 16));
	buffer.push_back((unsigned char)(i >> 8));
	buffer.push_back((unsigned char)i);
}

void Serializer::Pack(const unsigned long long i, std::vector<unsigned char>& buffer)
{
	buffer.push_back((unsigned char)(i >> 56));
	buffer.push_back((unsigned char)(i >> 48));
	buffer.push_back((unsigned char)(i >> 40));
	buffer.push_back((unsigned char)(i >> 32));
	buffer.push_back((unsigned char)(i >> 24));
	buffer.push_back((unsigned char)(i >> 16));
	buffer.push_back((unsigned char)(i >> 8));
	buffer.push_back((unsigned char)i);
}

void Serializer::Pack(const float i, std::vector<unsigned char>& buffer)
{
	unsigned int tempFloat = (unsigned int)Pack754(i, 32, 8);
	Pack(tempFloat, buffer);
}

void Serializer::Pack(const double i, std::vector<unsigned char>& buffer)
{
	unsigned __int64 tempDouble = Pack754(i, 64, 11);
	Pack(tempDouble, buffer);
}

void Serializer::Pack(const std::string i, std::vector<unsigned char>& buffer)
{
	Pack(i.size(), buffer);
	for_each(begin(i), end(i), [&buffer](char c) { Pack(c, buffer); });
}

void Serializer::Pack(const char i[], std::vector<unsigned char>& buffer)
{
	for (unsigned int j = 0; i[j] != '\0'; ++j)
	{
		Pack(i[j], buffer);
	}
	Pack((char)'\0', buffer);
}

void Serializer::Pack(char i[], std::vector<unsigned char>& buffer)
{
	Pack((const char*)i, buffer);
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, bool& i)
{
	i = buffer.at(index) != 0;
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, char& i)
{
	if (buffer.at(index) <= 0x7f)
	{
		i = buffer.at(index);
	}
	else
	{
		i = (-1 - (unsigned char)(0xffu - buffer.at(index)));
	}
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned char& i)
{
	i = buffer.at(index);
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, short& i)
{
	i = ((short)buffer.at(index) << 8) | buffer.at(index + 1);

	if (i > 0x7fffu)
	{
		i = -1 - (unsigned short)(0xffffu - i);
	}
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned short& i)
{
	i = ((unsigned int)buffer.at(index) << 8) | buffer.at(index + 1);
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, int& i)
{
	i = ((int)buffer.at(index) << 24) |
		((int)buffer.at(index + 1) << 16) |
		((int)buffer.at(index + 2) << 8) |
		((int)buffer.at(index + 3));

	if (i > 0x7fffffffu)
	{
		i = -1 - (int)(0xffffffffu - i);
	}
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned int& i)
{
	i = ((unsigned int)buffer.at(index) << 24) |
		((unsigned int)buffer.at(index + 1) << 16) |
		((unsigned int)buffer.at(index + 2) << 8) |
		((unsigned int)buffer.at(index + 3));
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, long long& i)
{
	i = ((long long)buffer.at(index) << 56) |
		((long long)buffer.at(index + 1) << 48) |
		((long long)buffer.at(index + 2) << 40) |
		((long long)buffer.at(index + 3) << 32) |
		((long long)buffer.at(index + 4) << 24) |
		((long long)buffer.at(index + 5) << 16) |
		((long long)buffer.at(index + 6) << 8) |
		(buffer.at(index + 7));

	if (i > 0x7fffffffffffffffu)
	{
		i = -1 - (__int64)(0xffffffffffffffffu - i);
	}
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned long long& i)
{
	i = ((unsigned long long)buffer.at(index) << 56) |
		((unsigned long long)buffer.at(index + 1) << 48) |
		((unsigned long long)buffer.at(index + 2) << 40) |
		((unsigned long long)buffer.at(index + 3) << 32) |
		((unsigned long long)buffer.at(index + 4) << 24) |
		((unsigned long long)buffer.at(index + 5) << 16) |
		((unsigned long long)buffer.at(index + 6) << 8) |
		((unsigned long long)buffer.at(index + 7));
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, float& i)
{
	unsigned int tempFloat;
	Unpack(buffer, index, tempFloat);
	i = (float)Unpack754(tempFloat, 32, 8);
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, double& i)
{
	unsigned __int64 tempDouble;
	Unpack(buffer, index, tempDouble);
	i = Unpack754(tempDouble, 64, 11);
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, std::string& i)
{
	unsigned int size;
	Unpack(buffer, index, size);
	i.reserve(size);
	for (unsigned int j = 0; j < size; ++j)
	{
		char c;
		Unpack(buffer, index + j + 4, c);
		i.push_back(c);
	}
}

void Serializer::Unpack(const std::vector<unsigned char>& buffer, const int index, char i[])
{
	char c = 'a';
	for (unsigned int j = 0; c != '\0'; ++j)
	{
		Unpack(buffer, index + j, c);
		i[j] = c;
	}
}

//Private
unsigned __int64 Serializer::Pack754(long double f, unsigned bits, unsigned expbits)
{
	long double fnorm;
	int shift;
	long long sign, exp, significand;
	unsigned significandbits = bits - expbits - 1; // -1 for sign bit

	if (f == 0.0)
		return 0; // get this special case out of the way

	// check sign and begin normalization
	if (f < 0)
	{
		sign = 1;
		fnorm = -f;
	}
	else
	{
		sign = 0;
		fnorm = f;
	}

	// get the normalized form of f and track the exponent
	shift = 0;
	while (fnorm >= 2.0)
	{
		fnorm /= 2.0;
		shift++;
	}

	while (fnorm < 1.0)
	{
		fnorm *= 2.0;
		shift--;
	}

	fnorm = fnorm - 1.0;

	// calculate the binary form (non-float) of the significand data
	significand = (long long)(fnorm * ((1LL << significandbits) + 0.5f));

	// get the biased exponent
	exp = shift + ((1 << (expbits - 1)) - 1); // shift + bias

	// return the final answer
	return (sign << (bits - 1)) | (exp << (bits - expbits - 1)) | significand;
}

long double Serializer::Unpack754(unsigned __int64 i, unsigned bits, unsigned expbits)
{
	long double result;
	long long shift;
	unsigned bias;
	unsigned significandbits = bits - expbits - 1; // -1 for sign bit

	if (i == 0)
		return 0.0;

	// pull the significand
	result = (long double)(i&((1LL << significandbits) - 1)); // mask
	result /= (1LL << significandbits); // convert back to float
	result += 1.0f; // add the one back on

	// deal with the exponent
	bias = (1 << (expbits - 1)) - 1;
	shift = ((i >> significandbits) & ((1LL << expbits) - 1)) - bias;
	while (shift > 0)
	{
		result *= 2.0;
		shift--;
	}
	while (shift < 0)
	{
		result /= 2.0;
		shift++;
	}

	// sign it
	result *= (i >> (bits - 1)) & 1 ? -1.0 : 1.0;

	return result;
}