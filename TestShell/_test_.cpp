#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(a, b) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
}
