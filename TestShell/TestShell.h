#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:
	const unsigned int ADDRESS_RANGE_MIN = 0;
	const unsigned int ADDRESS_RANGE_MAX = 99;

	TestShell(IDriver* driver_, std::ostream& output_ = std::cout);

	
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
	bool Script2();
	bool Script3();

	
private:
	IDriver* driver;
	std::ostream& out;

	void writeWithNewParam(unsigned int address, unsigned int writevalue);
	unsigned int readWithNewParam(unsigned int address);
	void writeFive(int loopCnt);
	bool readCompareFive(int address);
};