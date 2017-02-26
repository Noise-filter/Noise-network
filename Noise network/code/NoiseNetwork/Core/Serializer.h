#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <vector>
#include <string>

class Serializer
{
public:
	//Pack
	static void Pack(const bool i, std::vector<unsigned char>& buffer);
	
	static void Pack(const char i, std::vector<unsigned char>& buffer);
	static void Pack(const unsigned char i, std::vector<unsigned char>& buffer);
	
	static void Pack(const short i, std::vector<unsigned char>& buffer);
	static void Pack(const unsigned short i, std::vector<unsigned char>& buffer);
	
	static void Pack(const int i, std::vector<unsigned char>& buffer);
	static void Pack(const unsigned int i, std::vector<unsigned char>& buffer);
	
	static void Pack(const long long i, std::vector<unsigned char>& buffer);
	static void Pack(const unsigned long long i, std::vector<unsigned char>& buffer);
	
	static void Pack(const float i, std::vector<unsigned char>& buffer);
	static void Pack(const double i, std::vector<unsigned char>& buffer);

	static void Pack(const std::string i, std::vector<unsigned char>& buffer);
	static void Pack(const char i[], std::vector<unsigned char>& buffer);
	static void Pack(char i[], std::vector<unsigned char>& buffer);

	template<class ForwardIteratorType>
	static void Pack(ForwardIteratorType begin, ForwardIteratorType end, std::vector<unsigned char>& buffer)
	{
		unsigned int size = (unsigned int)std::distance(begin, end);
		Pack(size, buffer);
		while (begin != end)
		{
			Pack(*begin, buffer);
			++begin;
		}
	}

	//Unpack
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, bool& i);

	static void Unpack(const std::vector<unsigned char>& buffer, const int index, char& i);
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned char& i);

	static void Unpack(const std::vector<unsigned char>& buffer, const int index, short& i);
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned short& i);

	static void Unpack(const std::vector<unsigned char>& buffer, const int index, int& i);
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned int& i);

	static void Unpack(const std::vector<unsigned char>& buffer, const int index, long long& i);
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, unsigned long long& i);

	static void Unpack(const std::vector<unsigned char>& buffer, const int index, float& i);
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, double& i);

	static void Unpack(const std::vector<unsigned char>& buffer, const int index, std::string& i);
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, char i[]);

	template <class ContainerType>
	static void Unpack(const std::vector<unsigned char>& buffer, const int index, ContainerType& i)
	{
		unsigned int size;
		Unpack(buffer, index, size);
		for (unsigned int j = 0; j < size; j++)
		{
			typename ContainerType::value_type s;
			Unpack(buffer, index + (j * sizeof(s)) + 4, s);
			i.insert(end(i), s);
		}
	}

private:
	//Pack
	static unsigned __int64 Pack754(long double f, unsigned bits, unsigned expbits);

	//Unpack
	static long double Unpack754(unsigned __int64 i, unsigned bits, unsigned expbits);
};

#endif