#pragma once
#include "IDriver.h"
#include <iostream>

class TestShell {
public:
	TestShell(IDriver* driver_, std::ostream& output_ = std::cout);
	
	void help();
	unsigned int read(unsigned int address);
	std::vector<unsigned int> fullread();
	void write(unsigned int address, unsigned int data);
	void fullwrite(unsigned int data);
	void erase(unsigned int adress, int size);
	void erase_range(unsigned int start_address, unsigned int end_address);
	void flush();
	bool Script1();
	bool Script2();
	bool Script3();
	bool Script4();

	bool readCompare(unsigned int address, unsigned int value);

private:
	IDriver* driver;
	std::ostream& out;

	void writeFive(int loopCnt);
	bool readCompareFive(int address);
	void runEraseCommand(unsigned int address, int size);
};