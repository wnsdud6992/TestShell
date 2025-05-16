#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

class WriteFixture : public Test {
public:
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	const unsigned int NORMAL_ADDRESS = 3;
	const unsigned int NORMAL_DATA = 0xAAAABBBB;
	const unsigned int RANGE_OVER_ADDRESS = 100;
	const unsigned int RANGE_UNDER_ADDRESS = -1;
	std::vector<unsigned int> normal_param = { NORMAL_ADDRESS,NORMAL_DATA };
	std::vector<unsigned int> range_over_param = { RANGE_OVER_ADDRESS,NORMAL_DATA };
	std::vector<unsigned int> range_under_param = { RANGE_OVER_ADDRESS,NORMAL_DATA };
};

TEST_F(WriteFixture, NormalWritePass) {
	EXPECT_CALL(mockdriver, write(NORMAL_ADDRESS, NORMAL_DATA)).Times(1);
	testshell.write(normal_param);
}
TEST_F(WriteFixture, AddressRangeFail) {
	EXPECT_CALL(mockdriver, write(_,_)).Times(0);
	EXPECT_THROW(testshell.write(range_over_param), std::exception);
	EXPECT_THROW(testshell.write(range_under_param), std::exception);
}
