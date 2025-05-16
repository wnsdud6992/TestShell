#pragma once
#include "IDriver.h"
class TestShell {
public:
	TestShell(IDriver* driver_);
	void write(int address, int data);

private:
	IDriver* driver;
};