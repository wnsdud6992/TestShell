#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(WriteTest, NormalWritePass) {
	MockDriver mockdriver;
	EXPECT_CALL(mockdriver, write(3, 0xAAAABBBB)).Times(1);
	TestShell testshell{ &mockdriver };
	testshell.write(3, 0xAAAABBBB);
}
