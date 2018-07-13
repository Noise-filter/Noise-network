#ifndef PACKABLE_H
#define PACKABLE_H

#include <vector>

/*
 * Interface for classes that can be packed
 */
class Packable
{
public:
	virtual ~Packable() {}
	virtual std::vector<unsigned char> pack() const = 0;
	virtual void unpack(const std::vector<unsigned char>& bytes, unsigned int& index) = 0;
};

#endif