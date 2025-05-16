#include "TestShell.h"

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}
void TestShell::write(int address, int data) {
	if (address < 0 || address > 99)
		return;
	driver->write(address, data);
}



