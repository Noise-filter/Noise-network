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

	template<class T>
	static void Pack(std::vector<unsigned char>& buffer, const T& value) {
		Pack(value, buffer);
	}

	template<class U, class... T>
	static void Pack(std::vector<unsigned char>& buffer, const U& value, T&&... values) {
		Pack(value, buffer);
		Pack(buffer, std::forward<T>(values)...);
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

		i.resize(size);
		for (unsigned int j = 0; j < size; j++)
		{
			typename ContainerType::value_type value;
			newIndex = Unpack(buffer, newIndex, value);
			i.at(j) = value;
		}
		return newIndex;
	}

	template <class U, class... T>
	static unsigned int Unpack(const std::vector<unsigned char>& buffer, const unsigned int index, U& value, T&... values) {
		unsigned int i = UnpackTemplate(buffer, index, value);
		return Unpack(buffer, i, values...);
	}

private:
	template <class T>
	static unsigned int UnpackTemplate(const std::vector<unsigned char>& buffer, const unsigned int index, T& value) {
		return Unpack(buffer, index, value);
	}

	//Pack
	static unsigned __int64 Pack754(long double f, unsigned bits, unsigned expbits);

	//Unpack
	static long double Unpack754(unsigned __int64 i, unsigned bits, unsigned expbits);
};

#endif