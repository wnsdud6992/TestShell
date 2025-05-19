#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

class ScriptTestFixture : public Test {
public:
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::vector<unsigned int> TEST_ADDRESS = { 20 };
	const unsigned int TEST_VALUE = 0x1289CDEF;
};

TEST_F(ScriptTestFixture, ReadCompareTest) {
	EXPECT_CALL(mockdriver, read(TEST_ADDRESS[0])).WillOnce(Return(TEST_VALUE));
	EXPECT_TRUE(testshell.readCompare(TEST_ADDRESS, TEST_VALUE));
}
