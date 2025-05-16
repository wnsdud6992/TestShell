#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

class WriteFixture : public Test {
public:
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
};

TEST_F(WriteFixture, NormalWritePass) {
	EXPECT_CALL(mockdriver, write(3, 0xAAAABBBB)).Times(1);
	testshell.write(3, 0xAAAABBBB);
}
TEST_F(WriteFixture, AddressRangeOverFail) {
	EXPECT_CALL(mockdriver, write(_,_)).Times(0);
	EXPECT_THROW(testshell.write(testshell.ADDRESS_RANGE_MAX + 1, 0xAAAABBBB), std::exception);
	EXPECT_THROW(testshell.write(testshell.ADDRESS_RANGE_MIN - 1, 0xAAAABBBB), std::exception);
}
