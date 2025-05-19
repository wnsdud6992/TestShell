#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:
	const int ADDRESS_RANGE_MIN = 0;
	const int ADDRESS_RANGE_MAX = 99;

	TestShell(IDriver* driver_);
	void help();
	std::pair<std::string, std::vector<unsigned int>> parameterParsing(std::string& param);

	std::pair<unsigned int, unsigned int > CheckWriteParamValid(const std::vector<unsigned int>& command_param);
	void write(unsigned int address, unsigned int data);
	unsigned int CheckFullWriteParamValid(const std::vector<unsigned int>& command_param);
	void fullwrite(unsigned int data);

	unsigned int CheckReadParamValid(const std::vector<unsigned int>& param);
	unsigned int read(unsigned int address);
	std::vector<unsigned int> fullread();
	

	bool readCompare(unsigned int address, unsigned int value);
	void Script1();

	
private:
	IDriver* driver;

	void writeFive(int loopCnt);
	bool readCompareFive(int address);
};