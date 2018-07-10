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
	}

	virtual ~PackableClass()
	{}

	virtual std::vector<unsigned char> pack()
	{
		std::vector<unsigned char> buffer;
		Serializer::Pack(name, buffer);
		Serializer::Pack(age, buffer);
		Serializer::Pack(length, buffer);
		return buffer;
	}

	virtual void unpack(std::vector<unsigned char> bytes)
	{
		int index = 0;
		index = Serializer::Unpack(bytes, index, name);
		index = Serializer::Unpack(bytes, index, age);
		index = Serializer::Unpack(bytes, index, length);
	}

	void print()
	{
		std::cout << name << ' ' << age << ' ' << length << "m" << std::endl;
	}

private:
	std::string name;
	unsigned short age;
	float length;

};

#endif