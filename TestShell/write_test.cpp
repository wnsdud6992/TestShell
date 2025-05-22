#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

class WriteFixture : public Test {
public:
	MockDriver mockdriver;
	std::unique_ptr<MockDriver> driver = std::make_unique<MockDriver>();
	std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(driver));
	const unsigned int NORMAL_ADDRESS = 3;
	const unsigned int NORMAL_DATA = 0xAAAABBBB;
	const unsigned int MAX_LBA = 100 - 1;
	std::vector<unsigned int> normal_param = { NORMAL_ADDRESS,NORMAL_DATA };
	std::vector<unsigned int> arg_missing_param = { NORMAL_ADDRESS };
	std::vector<unsigned int> arg_over_param = { NORMAL_ADDRESS,NORMAL_DATA,NORMAL_DATA };
	std::vector<unsigned int> NORMAL_DATA_COMMAND = { NORMAL_DATA };
};

TEST_F(WriteFixture, DISABLED_NormalWritePass) {
	EXPECT_CALL(mockdriver, write(NORMAL_ADDRESS, NORMAL_DATA)).Times(1);
	testShell->write(NORMAL_ADDRESS, NORMAL_DATA);
}
TEST_F(WriteFixture, DISABLED_FullWritePass) {
	//Check write command cycle
	for (unsigned int address_index = 0; address_index <= MAX_LBA; address_index++) {
		EXPECT_CALL(mockdriver, write(address_index, NORMAL_DATA)).Times(1);
	}
	testShell->fullwrite(NORMAL_DATA);
}