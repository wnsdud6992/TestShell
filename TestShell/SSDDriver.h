#pragma once
#include "IDriver.h"

class SSDDriver : public IDriver {
public:
	SSDDriver() {}
	void write(unsigned int address, unsigned int value) override;
	unsigned int read(unsigned int address) override;
};