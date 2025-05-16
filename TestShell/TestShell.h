#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:
	const int ADDRESS_RANGE_MIN = 0;
	const int ADDRESS_RANGE_MAX = 99;

	TestShell(IDriver* driver_);
	void write(int address, int data);

	void help();

	std::pair<std::string, std::vector<int>> parameterParsing(std::string param);

private:
	IDriver* driver;
};