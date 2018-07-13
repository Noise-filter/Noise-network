#ifndef PACKABLE_CLASS_H
#define PACKABLE_CLASS_H

#include <iostream>
#include <string>

#include "Core\Package\BasePackage.h"

class PackableClass : public BasePackage
{
public:
	PackableClass() : BasePackage(0)
	{
		name = "Pontus Fredrik Fransson";
		age = 18;
		length = 1.78f;
		numbers.assign({1, 2, 3});
	}

	virtual ~PackableClass()
	{}

	virtual std::vector<unsigned char> pack() const
	{
		auto buffer = BasePackage::pack();
		Serializer::Pack(buffer, name, age, length, numbers);
		return buffer;
	}

	virtual void unpack(const std::vector<unsigned char>& bytes, unsigned int& index)
	{
		BasePackage::unpack(bytes, index);
		Serializer::Unpack(bytes, index, name, age, length, numbers);
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