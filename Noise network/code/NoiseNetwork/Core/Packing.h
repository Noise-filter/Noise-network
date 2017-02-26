#ifndef PACKING_H
#define PACKING_H

#include <vector>
#include "Packable.h"

class Packing
{
public:
	//bool (1-bit)
	static std::vector<unsigned char> pack(bool i);

	//char (8-bit)
	static std::vector<unsigned char> pack(char i);
	static std::vector<unsigned char> pack(unsigned char i);		// unsigned

	//short (16-bit)
	static std::vector<unsigned char> pack(short i);
	static std::vector<unsigned char> pack(unsigned short i);	// unsigned

	//int (32-bit)
	static std::vector<unsigned char> pack(int i);
	static std::vector<unsigned char> pack(unsigned int i);		// unsigned

	//__int64 (64-bit)
	static std::vector<unsigned char> pack(__int64 i);
	static std::vector<unsigned char> pack(unsigned __int64 i);	// unsigned

	//floating point (32, 64-bit)
	static std::vector<unsigned char> pack(float i);
	static std::vector<unsigned char> pack(double i);

	//string
	static std::vector<unsigned char> pack(char str[]);
	static std::vector<unsigned char> pack(std::string& str);

	//static std::vector<unsigned char> pack(Packable object);


	//bool (1-bit)
	static bool unpackb(unsigned char buffer[]);

	//char (8-bit)
	static char unpackc(unsigned char buffer[]);
	static unsigned char unpackC(unsigned char buffer[]);		// unsigned

	//short (16-bit)
	static short unpacks(unsigned char buffer[]);
	static unsigned short unpackS(unsigned char buffer[]);		// unsigned

	//int (32-bit)
	static int unpacki(unsigned char buffer[]);
	static unsigned int unpackI(unsigned char buffer[]);		// unsigned

	//__int64 (64-bit)
	static __int64 unpacki64(unsigned char buffer[]);
	static unsigned __int64 unpackI64(unsigned char buffer[]);	// unsigned

	//floating point (32, 64-bit)
	static float unpackf(unsigned char buffer[]);
	static double unpackd(unsigned char buffer[]);

	//string
	static char* unpackCStr(unsigned char buffer[]);
	static std::string unpackStr(unsigned char buffer[]);

private:
	Packing() {}

	static unsigned __int64 pack754(long double f, unsigned bits, unsigned expbits);

	static long double unpack754(unsigned __int64 i, unsigned bits, unsigned expbits);
};

#endif