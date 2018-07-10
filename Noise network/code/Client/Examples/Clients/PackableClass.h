#ifndef PACKABLE_CLASS_H
#define PACKABLE_CLASS_H

#include <iostream>
#include <string>

#include "Core\Packable.h"
#include "Core\Serializer.h"

class PackableClass : public Packable
{
public:
	PackableClass()
	{
		name = "Pontus Fredrik Fransson";
		age = 18;
		length = 1.78f;
		numbers.assign({1, 2, 3});
	}

	virtual ~PackableClass()
	{}

	virtual std::vector<unsigned char> pack()
	{
		std::vector<unsigned char> buffer;
		Serializer::Pack(buffer, name, age, length, numbers);

		//Serializer::Pack(name, buffer);
		//Serializer::Pack(age, buffer);
		//Serializer::Pack(length, buffer);
		return buffer;
	}

	virtual void unpack(const std::vector<unsigned char>& bytes)
	{
		int index = 0;
		Serializer::Unpack(bytes, index, name, age, length, numbers);
		//index = Serializer::Unpack(bytes, index, name);
		//index = Serializer::Unpack(bytes, index, age);
		//index = Serializer::Unpack(bytes, index, length);
	}

	void print()
	{
		std::cout << name << ' ' << age << ' ' << length << "m" << std::endl;
		for (auto& e : numbers) {
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	}

private:
	std::string name;
	unsigned short age;
	float length;
	std::vector<int> numbers;

};

#endif