#pragma once
#include "IDriver.h"
class TestShell {
public:
	TestShell(IDriver* driver_);

	void help();

	std::pair<std::string, std::vector<int>> parameterParsing(std::string param);

private:
	IDriver* driver;
};