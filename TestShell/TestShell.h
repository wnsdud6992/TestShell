#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:
	const int ADDRESS_RANGE_MIN = 0;
	const int ADDRESS_RANGE_MAX = 99;

	TestShell(IDriver* driver_);
	void write(std::vector<unsigned int> command_param);
	void fullwrite(std::vector<unsigned int> command_param);
	bool read(std::vector<unsigned int> address);
	bool fullread();

	void help();

	std::pair<std::string, std::vector<unsigned int>> parameterParsing(std::string &param);

private:
	IDriver* driver;
};