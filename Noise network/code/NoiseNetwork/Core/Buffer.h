#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include "Package/Packable.h"

class Buffer
{
public:
	virtual ~Buffer() = default;

	template <class T, typename std::enable_if<std::is_base_of<Packable, T>::value>::type* = nullptr>
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