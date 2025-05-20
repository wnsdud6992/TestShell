#pragma once
#include "Common.h"
#include "Logger.h"

class IDriver {
public:
	virtual void write(unsigned int address, unsigned int value) = 0;
	virtual unsigned int read(unsigned int address) = 0;
	virtual void setOutput(std::ostream* out) = 0;
};