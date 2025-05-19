#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:
	const unsigned int ADDRESS_RANGE_MIN = 0;
	const unsigned int ADDRESS_RANGE_MAX = 99;

	TestShell(IDriver* driver_);
	void write(std::vector<unsigned int> command_param);
	void fullwrite(std::vector<unsigned int> command_param);
	unsigned int read(std::vector<unsigned int> address);
	std::vector<unsigned int> fullread();
	bool Script3();

	void help();

	std::pair<std::string, std::vector<unsigned int>> parameterParsing(std::string &param);
	bool readCompare(std::vector<unsigned int >address, unsigned int value);
	void Script1();

	

private:
	IDriver* driver;

	void writeFive(int loopCnt);
	bool readCompareFive(int address);
};