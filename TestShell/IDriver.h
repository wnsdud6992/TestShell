#pragma once
#include "Common.h"

class IDriver {
public:
	virtual void write(int address, int value) = 0;
	virtual unsigned int read(unsigned int address) = 0;
};