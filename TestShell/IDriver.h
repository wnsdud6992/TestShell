#pragma once
#include "Common.h"

class IDriver {
public:
	virtual void write(int address, int value) = 0;
	virtual int read(int address) = 0;
};