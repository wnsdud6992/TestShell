#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

class ScriptTestFixture : public Test {
public:
	MockDriver mockdriver;
	std::unique_ptr<MockDriver> driver = std::make_unique<MockDriver>();
	std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(driver));
	const unsigned int TEST_ADDRESS { 20 };
	const unsigned int TEST_VALUE = 0x1289CDEF;

	const int StartAddress = 0;
	const int EndAddress = 99;
};

TEST_F(ScriptTestFixture, ReadCompareTest) {
	EXPECT_CALL(mockdriver, read(TEST_ADDRESS)).WillOnce(Return(TEST_VALUE));
	EXPECT_TRUE(testShell->readCompare(TEST_ADDRESS, TEST_VALUE));
}

TEST_F(ScriptTestFixture, Script1Test) {
	for (int iter = 0; iter < 20; iter++) {
		for (int idx = 0; idx < 5;idx++) {
			EXPECT_CALL(mockdriver, read(iter + idx)).WillOnce(Return(ScriptTest_Value + iter));
			EXPECT_TRUE(testShell->readCompare(iter + idx, ScriptTest_Value + iter));
		}
	}
}

