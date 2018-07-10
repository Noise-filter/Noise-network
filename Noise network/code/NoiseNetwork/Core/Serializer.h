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

	template<class Container>
	static void Pack(Container container, std::vector<unsigned char>& buffer)
	{
		size_t size = container.size();
		Pack(size, buffer);
		for (auto& e : container) {
			Pack(e, buffer);
		}
	}

	//Unpack
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, bool& i);

	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, char& i);
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, unsigned char& i);

	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, short& i);
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, unsigned short& i);

	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, int& i);
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, unsigned int& i);

	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, long long& i);
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, unsigned long long& i);

	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, float& i);
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, double& i);

	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, std::string& i);
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, char i[]);

	template <class ContainerType>
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, ContainerType& i)
	{
		unsigned int newIndex = index;
		size_t size;
		newIndex = Unpack(buffer, newIndex, size);
		for (unsigned int j = 0; j < size; j++)
		{
			typename ContainerType::value_type s;
			newIndex = Unpack(buffer, newIndex, s);
			i.insert(end(i), s);
		}
		return newIndex;
	}

private:
	//Pack
	static unsigned __int64 Pack754(long double f, unsigned bits, unsigned expbits);

	//Unpack
	static long double Unpack754(unsigned __int64 i, unsigned bits, unsigned expbits);
};

#endif