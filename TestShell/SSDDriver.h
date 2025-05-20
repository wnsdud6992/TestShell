#pragma once
#include "IDriver.h"

class SSDDriver : public IDriver {
public:
	SSDDriver() {}
	void write(unsigned int address, unsigned int value) override;
	unsigned int read(unsigned int address) override;
	void erase(unsigned int address, int size) override;

private:
	void runSSDWithParam(const std::string& param);
	unsigned int readSSDOutputFile();
};