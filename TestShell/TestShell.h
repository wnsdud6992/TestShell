#pragma once
#include "IDriver.h"
class TestShell {
public:
	TestShell(IDriver* driver_);

private:
	IDriver* driver;
};