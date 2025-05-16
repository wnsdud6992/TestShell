#include "TestShell.h"

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}
void TestShell::write(int address, int data) {
	driver->write(address, data);
}



