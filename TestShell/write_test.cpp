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
	std::vector<unsigned int> normal_param = { NORMAL_ADDRESS,NORMAL_DATA };
	std::vector<unsigned int> arg_missing_param = { NORMAL_ADDRESS };
	std::vector<unsigned int> arg_over_param = { NORMAL_ADDRESS,NORMAL_DATA,NORMAL_DATA };
	std::vector<unsigned int> NORMAL_DATA_COMMAND = { NORMAL_DATA };
};

TEST_F(WriteFixture, NormalWritePass) {
	EXPECT_CALL(mockdriver, write(NORMAL_ADDRESS, NORMAL_DATA)).Times(1);
	testshell.write(normal_param); 
}
TEST_F(WriteFixture, InvaildCommandFail) {
	EXPECT_CALL(mockdriver, write(_, _)).Times(0);
	EXPECT_THROW(testshell.write(arg_missing_param), std::exception);
	EXPECT_THROW(testshell.write(arg_over_param), std::exception);
}
TEST_F(WriteFixture, FullWritePass) {
	EXPECT_CALL(mockdriver, write(_, NORMAL_DATA)).Times(100);
	testshell.fullwrite(NORMAL_DATA_COMMAND);
}