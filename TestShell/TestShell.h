#pragma once
#include "IDriver.h"
#include <iostream>
class TestShell {
public:

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

	void erase(unsigned int adress, int size);
	void erase_range(unsigned int start_adress, unsigned int end_size);

	void Script1();
	bool Script2();
	bool Script3();

	
private:
	IDriver* driver;

	void writeWithNewParam(unsigned int address, unsigned int writevalue);
	unsigned int readWithNewParam(unsigned int address);
	void writeFive(int loopCnt);
	bool readCompareFive(int address);
};