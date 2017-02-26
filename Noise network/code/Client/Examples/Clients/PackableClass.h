#ifndef PACKABLE_CLASS_H
#define PACKABLE_CLASS_H

#include <iostream>
#include <string>

#include "Core\Packable.h"
#include "Core\Packing.h"

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
		std::vector<unsigned char> buffer = Packing::pack(name);

		std::vector<unsigned char> temp = Packing::pack(age);
		buffer.insert(std::end(buffer), std::begin(temp), std::end(temp));

		temp = Packing::pack(length);
		buffer.insert(std::end(buffer), std::begin(temp), std::end(temp));

		return buffer;
	}

	virtual void unpack(std::vector<unsigned char> bytes)
	{
		int index = 0;
		name = Packing::unpackStr(&bytes[index]);
		index += 2 + name.size();
		age = Packing::unpackS(&bytes[index]);
		index += 2;
		length = Packing::unpackf(&bytes[index]);
		index += 4;
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