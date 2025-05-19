#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ScriptTest, ReadCompareTest) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::vector<unsigned int> address = {20};
	unsigned int value = 0x1289CDEF;
	EXPECT_CALL(mockdriver, read(address[0])).WillOnce(Return(value));

	EXPECT_TRUE(testshell.readCompare(address, value));
}
