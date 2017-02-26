#include "packing.h"

using namespace std;

//bool (1-bit)
std::vector<unsigned char> Packing::pack(bool i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i);
	return buffer;
}

//char (8-bit)
std::vector<unsigned char> Packing::pack(char i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i);
	return buffer;
}

std::vector<unsigned char> Packing::pack(unsigned char i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i);
	return buffer;
}

//short (16-bit)
std::vector<unsigned char> Packing::pack(short i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i >> 8);
	buffer.insert(buffer.end(), (char)i);
	return buffer;
}

std::vector<unsigned char> Packing::pack(unsigned short i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i >> 8);
	buffer.insert(buffer.end(), (char)i);
	return buffer;
}

//int (32-bit)
std::vector<unsigned char> Packing::pack(int i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i >> 24);
	buffer.insert(buffer.end(), i >> 16);
	buffer.insert(buffer.end(), i >> 8);
	buffer.insert(buffer.end(), i);
	return buffer;
}

std::vector<unsigned char> Packing::pack(unsigned int i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), i >> 24);
	buffer.insert(buffer.end(), i >> 16);
	buffer.insert(buffer.end(), i >> 8);
	buffer.insert(buffer.end(), i);
	return buffer;
}

//__int64 (64-bit)
std::vector<unsigned char> Packing::pack(__int64 i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), (char)(i >> 56));
	buffer.insert(buffer.end(), (char)(i >> 48));
	buffer.insert(buffer.end(), (char)(i >> 40));
	buffer.insert(buffer.end(), (char)(i >> 32));
	buffer.insert(buffer.end(), (char)(i >> 24));
	buffer.insert(buffer.end(), (char)(i >> 16));
	buffer.insert(buffer.end(), (char)(i >> 8));
	buffer.insert(buffer.end(), (char)i);
	return buffer;
}

std::vector<unsigned char> Packing::pack(unsigned __int64 i)
{
	std::vector<unsigned char> buffer;
	buffer.insert(buffer.end(), (char)(i >> 56));
	buffer.insert(buffer.end(), (char)(i >> 48));
	buffer.insert(buffer.end(), (char)(i >> 40));
	buffer.insert(buffer.end(), (char)(i >> 32));
	buffer.insert(buffer.end(), (char)(i >> 24));
	buffer.insert(buffer.end(), (char)(i >> 16));
	buffer.insert(buffer.end(), (char)(i >> 8));
	buffer.insert(buffer.end(), (char)i);
	return buffer;
}

//floating point (32, 64-bit)
std::vector<unsigned char> Packing::pack(float i)
{
	std::vector<unsigned char> buffer;
	int tempFloat = (int)pack754(i, 32, 8);
	buffer = pack(tempFloat);
	return buffer;
}

std::vector<unsigned char> Packing::pack(double i)
{
	std::vector<unsigned char> buffer;
	__int64 tempDouble = pack754(i, 64, 11);
	buffer = pack(tempDouble);
	return buffer;
}

//string
std::vector<unsigned char> Packing::pack(char str[])
{
	std::vector<unsigned char> buffer;
	unsigned short len = (unsigned short)strlen(str);
	buffer = pack(len);
	buffer.insert(buffer.end(), &str[0], &str[len]);
	return buffer;
}

std::vector<unsigned char> Packing::pack(std::string& str)
{
	std::vector<unsigned char> buffer;
	unsigned short len = (unsigned short)str.length();
	buffer = pack(len);
	buffer.insert(buffer.end(), str.begin(), str.end());
	return buffer;
}

unsigned __int64 Packing::pack754(long double f, unsigned bits, unsigned expbits)
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

//bool (1-bit)
bool Packing::unpackb(unsigned char buffer[])
{
	return (*buffer) != 0;
}

//char (8-bit)
char Packing::unpackc(unsigned char buffer[])
{
	if (*buffer <= 0x7f)
	{
		return *buffer;
	}
	else
	{
		return (-1 - (unsigned char)(0xffu - *buffer));
	}
}

unsigned char Packing::unpackC(unsigned char buffer[])
{
	return *buffer;
}

//short (16-bit)
short Packing::unpacks(unsigned char buffer[])
{
	short i = ((short)buffer[0] << 8) | buffer[1];

	if (i > 0x7fffu)
	{
		i = -1 - (unsigned short)(0xffffu - i);
	}

	return i;
}

unsigned short Packing::unpackS(unsigned char buffer[])
{
	return ((unsigned int)buffer[0] << 8) | buffer[1];
}

//int (32-bit)
int Packing::unpacki(unsigned char buffer[])
{
	int i = ((int)buffer[0] << 24) |
		((int)buffer[1] << 16) |
		((int)buffer[2] << 8) |
		((int)buffer[3]);

	if (i > 0x7fffffffu)
	{
		i = -1 - (int)(0xffffffffu - i);
	}

	return i;
}

unsigned int Packing::unpackI(unsigned char buffer[])
{
	return ((unsigned int)buffer[0] << 24) |
		((unsigned int)buffer[1] << 16) |
		((unsigned int)buffer[2] << 8) |
		((unsigned int)buffer[3]);
}

//__int64 (64-bit)
__int64 Packing::unpacki64(unsigned char buffer[])
{
	__int64 i = ((__int64)buffer[0] << 56) |
		((__int64)buffer[1] << 48) |
		((__int64)buffer[2] << 40) |
		((__int64)buffer[3] << 32) |
		((__int64)buffer[4] << 24) |
		((__int64)buffer[5] << 16) |
		((__int64)buffer[6] << 8) |
		(buffer[7]);

	if (i > 0x7fffffffffffffffu)
	{
		i = -1 - (__int64)(0xffffffffffffffffu - i);
	}

	return i;
}

unsigned __int64 Packing::unpackI64(unsigned char buffer[])
{
	return ((__int64)buffer[0] << 56) |
		((__int64)buffer[1] << 48) |
		((__int64)buffer[2] << 40) |
		((__int64)buffer[3] << 32) |
		((__int64)buffer[4] << 24) |
		((__int64)buffer[5] << 16) |
		((__int64)buffer[6] << 8) |
		((__int64)buffer[7]);
}

//floating point (32, 64-bit)
float Packing::unpackf(unsigned char buffer[])
{
	int tempFloat = unpacki(buffer);
	return (float)unpack754(tempFloat, 32, 8);
}

double Packing::unpackd(unsigned char buffer[])
{
	__int64 tempDouble = unpacki64(buffer);
	return unpack754(tempDouble, 64, 11);
}

//string
char* Packing::unpackCStr(unsigned char buffer[])
{
	unsigned short len = unpackS(buffer);
	char* str = new char[len + 1];

	buffer += 2;
	for (int i = 0; i < len; i++)
	{
		str[i] = buffer[i];
	}

	str[len] = '\0';

	return str;
}

std::string Packing::unpackStr(unsigned char buffer[])
{
	unsigned short len = unpackS(buffer);
	std::string temp;
	temp.resize(len);

	buffer += 2;
	for (int i = 0; i < len; i++)
	{
		temp[i] = buffer[i];
	}

	return temp;
}

long double Packing::unpack754(unsigned __int64 i, unsigned bits, unsigned expbits)
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