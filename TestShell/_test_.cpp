#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(a, b) {
	MockDriver mockdriver;
	std::unique_ptr<MockDriver> driver = std::make_unique<MockDriver>();
	std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(driver));
}
