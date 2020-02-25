#pragma once

#include "BasePackage.h"

#include <ostream>

enum class PackageErrors {
	PACKAGE_NOT_REGISTERED = -100,
	NOT_CONNECTED,

};

class ErrorPackage : public BasePackage {
private:
	PackageErrors errorCode;

public:
	constexpr ErrorPackage(PackageErrors error = PackageErrors::PACKAGE_NOT_REGISTERED) : BasePackage(PACKAGE_ID), errorCode(error) {
	}

	virtual ~ErrorPackage() = default;

	constexpr PackageErrors getErrorCode() {
		return errorCode;
	}

	virtual BasePackage* createInstance() {
		return new ErrorPackage;
	}

	static constexpr int PACKAGE_ID = -1;
};