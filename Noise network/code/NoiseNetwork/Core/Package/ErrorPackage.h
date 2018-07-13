#pragma once

#include "BasePackage.h"

enum PackageErrors {
	PACKAGE_NOT_REGISTERED = -100,
	NOT_CONNECTED,

};

class ErrorPackage : public BasePackage {
private:
	int errorCode;

public:
	ErrorPackage(int error = 0) : BasePackage(PACKAGE_ID), errorCode(error) {
	}

	virtual ~ErrorPackage() { }

	int getErrorCode() {
		return errorCode;
	}

	static const int PACKAGE_ID = 1;
};