#pragma once
#include "IDriver.h"

class SSDDriver : public IDriver {
public:
	SSDDriver() : out(&std::cout) {}
	void write(unsigned int address, unsigned int value) override;
	unsigned int read(unsigned int address) override;
	void setoutput(std::ostream* output) override;
	void erase(unsigned int address, unsigned int size) override;
	void flush() override;

private:
	void runSSDWithParam(const std::string& param);
	unsigned int readSSDOutputFile();
	std::ostream* out;
};