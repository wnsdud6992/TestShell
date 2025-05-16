#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:
	const int ADDRESS_RANGE_MIN = 0;
	const int ADDRESS_RANGE_MAX = 99;

	TestShell(IDriver* driver_);
	void write(std::vector<unsigned int> command_param);

	void help();

	std::pair<std::string, std::vector<int>> parameterParsing(std::string param);

private:
	IDriver* driver;
};