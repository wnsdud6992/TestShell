#pragma once
#include "Common.h"

class IDriver {
public:
	virtual void write(unsigned int address, unsigned int value) = 0;
	virtual unsigned int read(unsigned int address) = 0;
	virtual void erase(unsigned int address, unsigned int size) = 0;
};