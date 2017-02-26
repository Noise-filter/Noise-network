#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include "Packable.h"
#include "Packing.h"

class Buffer
{
public:
	Buffer();
	virtual ~Buffer();

	template <class T>
	void pack(T object)
	{
		std::vector<unsigned char> asd = Packing::pack(object);
		buffer.insert(buffer.end(), asd.begin(), asd.end());
	}

	template<class T>
	T unpack()
	{

	}

private:
	std::vector<unsigned char> buffer;
	int index = 0;
};

#endif