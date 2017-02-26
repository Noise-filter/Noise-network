#ifndef PACKABLE_H
#define PACKABLE_H

#include <vector>

/*
 * Interface for classes that can be packed
 */
class Packable
{
public:
	virtual std::vector<unsigned char> pack() = 0;
	virtual void unpack(std::vector<unsigned char> bytes) = 0;
};

#endif