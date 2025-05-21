#pragma once
#include "IDriver.h"

class SSDDriver : public IDriver {
public:
	SSDDriver() : out(&std::cout) {}
	void write(unsigned int address, unsigned int value) override;
	unsigned int read(unsigned int address) override;
	void erase(unsigned int address, unsigned int size) override;
	void flush() override;

	void setoutput(std::ostream* output) override;

private:
	void runFunc(const std::string option, const unsigned int param1, const unsigned int param2);
	unsigned int readSSDOutputFile();
	std::ostream* out;
};