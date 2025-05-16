#include "TestShell.h"

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}
void TestShell::write(int address, int data) {
	if (address < ADDRESS_RANGE_MIN || address > ADDRESS_RANGE_MAX) {
		throw std::exception("address range over");
		return;
	}
	driver->write(address, data);
}



