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
	const unsigned int MAX_LBA = 100 - 1;
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
	EXPECT_THROW(testshell.write(arg_missing_param), CustomException);
	EXPECT_THROW(testshell.write(arg_over_param), CustomException);
	EXPECT_THROW(testshell.fullwrite(normal_param), CustomException);
}
TEST_F(WriteFixture, FullWritePass) {
	//Check write command cycle
	for (unsigned int address_index = 0; address_index <= MAX_LBA; address_index++) {
		EXPECT_CALL(mockdriver, write(address_index, NORMAL_DATA)).Times(1);
	}
	testshell.fullwrite(NORMAL_DATA_COMMAND);
}