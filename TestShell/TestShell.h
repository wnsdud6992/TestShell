#pragma once
#include "IDriver.h"
class TestShell {
public:
	TestShell(IDriver* driver_);

	void help();

private:
	IDriver* driver;
};