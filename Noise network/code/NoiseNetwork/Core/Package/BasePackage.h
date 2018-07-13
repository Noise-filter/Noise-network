#pragma once

#include "Packable.h"
#include "Serializer.h"

class BasePackage : Packable {
private:
	unsigned int size = 0;
	int id;
	// Timestamp?

public:
	BasePackage(int id) : id(id) {
	}

	virtual ~BasePackage() {

	}

	virtual std::vector<unsigned char> pack() const {
		std::vector<unsigned char> buffer;
		Serializer::Pack(buffer, size, id);
		return buffer;
	}

	virtual void unpack(const std::vector<unsigned char>& bytes, unsigned int& index) {
		index = Serializer::Unpack(bytes, index, size, id);
	}

	int getSize() {
		return size;
	}

	int getId() {
		return id;
	}
};