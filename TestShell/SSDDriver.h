#pragma once
#include "IDriver.h"

class SSDDriver : public IDriver {
public:
	SSDDriver() {}
	void write(int address, int value) override;
	unsigned int read(int address) override;
};