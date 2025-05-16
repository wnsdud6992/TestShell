#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <memory>

class IDriver {
public:
	virtual void write(int address, int value) = 0;
	virtual int read(int address) = 0;
};