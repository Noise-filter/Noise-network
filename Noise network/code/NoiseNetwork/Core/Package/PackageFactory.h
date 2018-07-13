#pragma once

#include <map>
#include <functional>
#include "BasePackage.h"
#include "ErrorPackage.h"

class PackageFactory {
public:
	static PackageFactory& getInstance() {
		static PackageFactory instance;
		return instance;
	}

	PackageFactory(const PackageFactory& factory) = delete;
	void operator=(const PackageFactory& factory) = delete;

	void registerPackage(int id, std::function<BasePackage*()> createFunction) {
		registeredPackages.insert({ id, createFunction });
	}

	std::unique_ptr<BasePackage> create(int id) {
		if (registeredPackages.find(id) == end(registeredPackages)) {
			return std::make_unique<ErrorPackage>(PackageErrors::PACKAGE_NOT_REGISTERED);
		}
		return std::unique_ptr<BasePackage>(registeredPackages.at(id)());
	}

private:
	PackageFactory() {}

	std::map<int, std::function<BasePackage*()>> registeredPackages;

};